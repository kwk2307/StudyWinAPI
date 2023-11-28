#pragma once
class WindowsGDI
{
public:
	bool initialize(const Screen& InScreenSize);
	void Release();

	void SwapBuffer();
protected:
	bool m_bGDIInitialized = false;

	HWND m_hwndHandle = 0;
	HDC	m_hdcScreenDC = 0, m_hdcMemoryDC = 0;
	HBITMAP m_bitmapDefaultBitmap = 0, m_bitmapDIBitmap = 0;

	Screen m_ScreenSize;

public:
	~WindowsGDI();
};

