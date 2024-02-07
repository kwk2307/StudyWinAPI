#include "Precomplied.h"

bool WindowsRenderer::Init(const ScreenPoint& InSize) {
	
	Release();

	if (_Handle == 0) {
		// 현재 활성화 돼있는 윈도우 핸들러를 받아옴
		_Handle = GetActiveWindow();
		// 실패한 경우 종료
		if (_Handle == 0) {
			return false;
		}
	}
	
	// 현재 DC를 받아옴
	_ScreenDC = GetDC(_Handle);
	if (_ScreenDC == NULL)
	{
		return false;
	}

	// 스왑 체인용 DC를 만들어줌 
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