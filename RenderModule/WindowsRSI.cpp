#include "Precompiled.h"

WindowsRSI::~WindowsRSI()
{
}

bool WindowsRSI::Init(const ScreenPoint& InSize)
{
	return initialize(InSize);
}

void WindowsRSI::Shutdown()
{
	Release();
}

void WindowsRSI::Clear(const LinearColor& InClearColor)
{
	Rectangle(m_hdcMemoryDC, -1, -1, m_ScreenSize.x + 1, m_ScreenSize.y + 1);
}

void WindowsRSI::BeginFrame()
{
}

void WindowsRSI::EndFrame()
{
	SwapBuffer();
}

void WindowsRSI::DrawPoint(const ScreenPoint& _point) const
{

}

bool WindowsRSI::initialize(const ScreenPoint& _ScreenSize)
{
	Release();

	if (m_hwndHandle == 0)
	{
		m_hwndHandle = GetActiveWindow();
		if (m_hwndHandle == 0)
		{
			return false;
		}
	}

	if (m_bGDIInitialized)
	{
		DeleteObject(m_bitmapDefaultBitmap);
		DeleteObject(m_bitmapDIBitmap);
		ReleaseDC(m_hwndHandle, m_hdcScreenDC);
		ReleaseDC(m_hwndHandle, m_hdcMemoryDC);
	}

	m_hdcScreenDC = GetDC(m_hwndHandle);
	if (m_hdcScreenDC == NULL)
	{
		return false;
	}

	m_hdcMemoryDC = CreateCompatibleDC(m_hdcScreenDC);
	if (m_hdcMemoryDC == NULL)
	{
		return false;
	}
	// ∫Ò∆Æ∏  ∏∏µÈ∞Ì
	m_bitmapDIBitmap = CreateCompatibleBitmap(m_hdcScreenDC, _ScreenSize.x, _ScreenSize.y);
	// ±‚¡∏ ∫Ò∆Æ∏  ¿˙¿Â«ÿµ“
	m_bitmapDefaultBitmap = (HBITMAP)SelectObject(m_hdcMemoryDC, m_bitmapDIBitmap);
	if (m_bitmapDefaultBitmap == NULL)
	{
		return false;
	}

	m_ScreenSize = _ScreenSize;
	m_bGDIInitialized = true;

	return true;
}

void WindowsRSI::Release()
{
	if (m_bGDIInitialized) {
		DeleteObject(m_bitmapDefaultBitmap);
		DeleteObject(m_bitmapDIBitmap);
		ReleaseDC(m_hwndHandle, m_hdcScreenDC);
		ReleaseDC(m_hwndHandle, m_hdcMemoryDC);
	}
	m_bGDIInitialized = false;
}

void WindowsRSI::SwapBuffer()
{
	BitBlt(m_hdcScreenDC, 0, 0, m_ScreenSize.x, m_ScreenSize.y, m_hdcMemoryDC, 0, 0, SRCCOPY);
}

