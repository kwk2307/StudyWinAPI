#include "Precompiled.h"

bool WindowsRenderer::Init(const ScreenPoint& InSize) {
	
	Release();

	if (_Handle == 0) {
		// ���� Ȱ��ȭ ���ִ� ������ �ڵ鷯�� �޾ƿ�
		_Handle = GetActiveWindow();
		// ������ ��� ����
		if (_Handle == 0) {
			return false;
		}
	}
	
	// ���� DC�� �޾ƿ�
	_ScreenDC = GetDC(_Handle);
	if (_ScreenDC == NULL)
	{
		return false;
	}

	// ���� ü�ο� DC�� ������� 
	_MemoryDC = CreateCompatibleDC(_ScreenDC);
	if (_MemoryDC == NULL)
	{
		return false;
	}

	_ScreenSize = InSize;

	// Color & Bitmap Setting
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = _ScreenSize.X;
	bmi.bmiHeader.biHeight = -_ScreenSize.Y;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	DIBitmap = CreateDIBSection(_MemoryDC, &bmi, DIB_RGB_COLORS, (void**)&_ScreenBuffer, NULL, 0);
	if (DIBitmap == NULL)
	{
		return false;
	}

	_DefaultBitmap = (HBITMAP)SelectObject(_MemoryDC, DIBitmap);
	if (_DefaultBitmap == NULL)
	{
		return false;
	}

	_Initialized = true;
	return true;
}

void WindowsRenderer::Shutdown()
{
	Release();
}

void WindowsRenderer::Clear(const Color& InClearColor)
{
	FillBuffer(InClearColor);
}

void WindowsRenderer::BeginFrame()
{
}

void WindowsRenderer::EndFrame()
{
	SwapBuffer();
}

void WindowsRenderer::DrawPoint(const ScreenPoint& InScreenPos, const Color& InColor)
{
	Color bufferColor = GetPixel(InScreenPos);

	if (!IsInScreen(InScreenPos))
	{
		return;
	}

	Color* dest = _ScreenBuffer;
	*(dest + GetScreenBufferIndex(InScreenPos)) = 
		(InColor * (InColor.A/255)) + 
		(bufferColor * ((255 - InColor.A) / 255));
	
	return;
}

void WindowsRenderer::DrawLine(const Vector4& InStartPos, const Vector4& InEndPos, const Color& InColor)
{
	Vector2 clippedStart = InStartPos.ToVector2();
	Vector2 clippedEnd = InEndPos.ToVector2();
	Vector2 screenExtend = Vector2(_ScreenSize.X, _ScreenSize.Y) * 0.5f;
	Vector2 minScreen = -screenExtend;
	Vector2 maxScreen = screenExtend;
	if (!CohenSutherlandLineClip(clippedStart, clippedEnd, minScreen, maxScreen))
	{
		return;
	}

	ScreenPoint startPosition = ScreenPoint::ToScreenCoordinate(_ScreenSize, clippedStart);
	ScreenPoint endPosition = ScreenPoint::ToScreenCoordinate(_ScreenSize, clippedEnd);

	int width = endPosition.X - startPosition.X;
	int height = endPosition.Y - startPosition.Y;

	bool isGradualSlope = (MathUtil::Abs(width) >= MathUtil::Abs(height));
	int dx = (width >= 0) ? 1 : -1;
	int dy = (height > 0) ? 1 : -1;
	int fw = dx * width;
	int fh = dy * height;

	int f = isGradualSlope ? fh * 2 - fw : 2 * fw - fh;
	int f1 = isGradualSlope ? 2 * fh : 2 * fw;
	int f2 = isGradualSlope ? 2 * (fh - fw) : 2 * (fw - fh);
	int x = startPosition.X;
	int y = startPosition.Y;

	if (isGradualSlope)
	{
		while (x != endPosition.X)
		{
			DrawPoint(ScreenPoint(x, y), InColor);

			if (f < 0)
			{
				f += f1;
			}
			else
			{
				f += f2;
				y += dy;
			}

			x += dx;
		}
	}
	else
	{
		while (y != endPosition.Y)
		{
			DrawPoint(ScreenPoint(x, y), InColor);

			if (f < 0)
			{
				f += f1;
			}
			else
			{
				f += f2;
				x += dx;
			}

			y += dy;
		}
	}
}

void WindowsRenderer::Release()
{
	if (_Initialized) {
		DeleteObject(_DefaultBitmap);
		DeleteObject(DIBitmap);
		ReleaseDC(_Handle, _ScreenDC);
		ReleaseDC(_Handle, _MemoryDC);
	}

	_Initialized = false;
}

void WindowsRenderer::FillBuffer(Color InColor)
{
	if (!_Initialized || (_ScreenBuffer == NULL)) {
		return;
	}
	UINT32 totalCount = _ScreenSize.X * _ScreenSize.Y;
	CopyBuffer<Color>(_ScreenBuffer, &InColor, totalCount);
	return;
}

bool WindowsRenderer::IsInScreen(const ScreenPoint& InPos) const
{
	if ((InPos.X < 0 || InPos.X >= _ScreenSize.X) || (InPos.Y < 0 || InPos.Y >= _ScreenSize.Y))
	{
		return false;
	}

	return true;
}

int WindowsRenderer::GetScreenBufferIndex(const ScreenPoint& InPos) const
{
	return InPos.Y * _ScreenSize.X + InPos.X;
}


int WindowsRenderer::TestRegion(const Vector2& InVectorPos, const Vector2& InMinPos, const Vector2& InMaxPos)
{
	int result = 0;
	if (InVectorPos.X < InMinPos.X)
	{
		result = result | 0b0001;
	}
	else if (InVectorPos.X > InMaxPos.X)
	{
		result = result | 0b0010;
	}

	if (InVectorPos.Y < InMinPos.Y)
	{
		result = result | 0b0100;
	}
	else if (InVectorPos.Y > InMaxPos.Y)
	{
		result = result | 0b1000;
	}

	return result;
}

bool WindowsRenderer::CohenSutherlandLineClip(Vector2& InOutStartPos, Vector2& InOutEndPos, const Vector2& InMinPos, const Vector2& InMaxPos)
{
	int startTest = TestRegion(InOutStartPos, InMinPos, InMaxPos);
	int endTest = TestRegion(InOutEndPos, InMinPos, InMaxPos);

	float width = (InOutEndPos.X - InOutStartPos.X);
	float height = (InOutEndPos.Y - InOutStartPos.Y);

	while (true)
	{
		if ((startTest == 0) && (endTest == 0)) // ȭ�� �ȿ� �� ���� ������ �ٷ� �׸���
		{
			return true;
		}
		else if (startTest & endTest) // ȭ�� �ۿ� ���� �����Ƿ� �׸� �ʿ䰡 ����
		{
			return false;
		}
		else // ������ ������ Ŭ���� ����
		{
			Vector2 clippedPosition;
			bool isStartTest = (startTest != 0);
			int currentTest = isStartTest ? startTest : endTest;

			if (currentTest < 0b0100)
			{
				if (currentTest & 1)
				{
					clippedPosition.X = InMinPos.X;
				}
				else
				{
					clippedPosition.X = InMaxPos.X;
				}

				if (MathUtil::EqualsInTolerance(height, 0.0f))
				{
					clippedPosition.Y = InOutStartPos.Y;

				}
				else
				{
					clippedPosition.Y = InOutStartPos.Y + height * (clippedPosition.X - InOutStartPos.X) / width;
				}
			}
			else
			{
				if (currentTest & 0b0100)
				{
					clippedPosition.Y = InMinPos.Y;
				}
				else
				{
					clippedPosition.Y = InMaxPos.Y;
				}

				if (MathUtil::EqualsInTolerance(width, 0.0f))
				{
					clippedPosition.X = InOutStartPos.X;
				}
				else
				{
					clippedPosition.X = InOutStartPos.X + width * (clippedPosition.Y - InOutStartPos.Y) / height;
				}
			}

			// Ŭ������ ����� �ٽ� �׽�Ʈ ����.
			if (isStartTest)
			{
				InOutStartPos = clippedPosition;
				startTest = TestRegion(InOutStartPos, InMinPos, InMaxPos);
			}
			else
			{
				InOutEndPos = clippedPosition;
				endTest = TestRegion(InOutEndPos, InMinPos, InMaxPos);
			}
		}
	}
}

Color WindowsRenderer::GetPixel(const ScreenPoint& InPos)
{
	if (!IsInScreen(InPos)) {
		return Color::Error;
	}
	Color* dest = _ScreenBuffer;
	
	return *(dest + GetScreenBufferIndex(InPos));
}

void WindowsRenderer::SwapBuffer()
{
	if (!_Initialized)
	{
		return;
	}

	BitBlt(_ScreenDC, 0, 0, _ScreenSize.X, _ScreenSize.Y, _MemoryDC, 0, 0, SRCCOPY);
}

template <class T>
T* WindowsRenderer::CopyBuffer(T* InDst, T* InSrc, int InCount)
{
	if (InCount == 0)
	{
		return NULL;
	}

	if (InCount == 1)
	{
		memcpy(InDst, InSrc, sizeof(T));
	}
	else
	{
		int half = MathUtil::FloorToInt(InCount * 0.5f);
		CopyBuffer<T>(InDst, InSrc, half);
		memcpy(InDst + half, InDst, half * sizeof(T));

		if (InCount % 2)
		{
			memcpy(InDst + (InCount - 1), InSrc, sizeof(T));
		}
	}

	return InDst;
}