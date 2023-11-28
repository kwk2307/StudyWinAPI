#include "Precompiled.h"

bool WindowsGDI::initialize(const Screen& _ScreenSize)
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

void WindowsGDI::Release()
{
	if (m_bGDIInitialized) {
		DeleteObject(m_bitmapDefaultBitmap);
		DeleteObject(m_bitmapDIBitmap);
		ReleaseDC(m_hwndHandle, m_hdcScreenDC);
		ReleaseDC(m_hwndHandle, m_hdcMemoryDC);
	}
	m_bGDIInitialized = false;
}

void WindowsGDI::SwapBuffer()
{
	BitBlt(m_hdcScreenDC, 0, 0, m_ScreenSize.x, m_ScreenSize.y, m_hdcMemoryDC, 0, 0, SRCCOPY);
}

WindowsGDI::~WindowsGDI()
{
}
