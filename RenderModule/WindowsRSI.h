#pragma once
class WindowsRSI: public RendererInterface
{
public:
	WindowsRSI() = default;
	~WindowsRSI();

public:
	virtual bool Init(const ScreenPoint& InSize) override;
	virtual void Shutdown() override;
	virtual bool IsInitialized() { return m_bGDIInitialized; }

	virtual void Clear(const LinearColor& InClearColor) override;
	virtual void BeginFrame() override;
	virtual void EndFrame() override;

	virtual void DrawPoint(const ScreenPoint& _point) const override;

public:
	bool initialize(const ScreenPoint& InScreenSize);
	void Release();

	void SwapBuffer();
protected:
	bool m_bGDIInitialized = false;

	HWND m_hwndHandle = 0;
	HDC	m_hdcScreenDC = 0, m_hdcMemoryDC = 0;
	HBITMAP m_bitmapDefaultBitmap = 0, m_bitmapDIBitmap = 0;

	ScreenPoint m_ScreenSize;
};
