#pragma once
class WindowsRenderer: public RendererInterface
{
public:
	virtual bool Init(const ScreenPoint& InSize) override;
	virtual void Shutdown() override;
	virtual bool IsInitialized() const { return _Initialized; }

	virtual void Clear(const Color& InClearColor) override;
	virtual void BeginFrame() override;
	virtual void EndFrame() override;

public:
	virtual void DrawPoint(const ScreenPoint& InScreenPos, const Color& InColor) override;
private:
	void Release();
	void FillBuffer(Color InColor);

	bool IsInScreen(const ScreenPoint& InPos) const;
	int  GetScreenBufferIndex(const ScreenPoint& InPos) const;

	Color GetPixel(const ScreenPoint& InPos);

	template <class T>
	T* CopyBuffer(T* InDst, T* InSrc, int InCount);

	void SwapBuffer();

private:
	bool _Initialized = false;

	HWND _Handle = 0;
	HDC	_ScreenDC = 0, _MemoryDC = 0;
	HBITMAP _DefaultBitmap = 0, DIBitmap = 0;

	Color* _ScreenBuffer = nullptr;

	ScreenPoint _ScreenSize;

};

