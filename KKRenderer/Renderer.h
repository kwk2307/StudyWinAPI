#pragma once
class Renderer
{
public:
	Renderer(RendererInterface* RI);

	void Tick();

	float GetFrameFPS() const { return _FrameFPS; }
	float GetElapsedTime() const { return _ElapsedTime; }
	float GetAverageFPS() const { return _AverageFPS; }

	// 성능 측정
	std::function<float()> _PerformanceInitFunc;
	std::function<INT64()> _PerformanceMeasureFunc;
	//std::function<void(InputManager&)> _InputBindingFunc;

	void OnResize(const ScreenPoint& InScreeSize);
	GameEngine& GetGameEngine() { return _GameEngine; }

private:
	RendererInterface& GetRenderer() { return *_RIPtr.get(); }

	void PreUpdate();
	void PostUpdate();

	void LoadScene(std::string& SceneName);
	void Update(float InDeltaSeconds);
	void LateUpdate(float InDeltaSeconds);
	void Render();

public:

private:
	// 초기화 점검 변수
	bool _PerformanceCheckInitialized = false;
	bool _RendererInitialized = false;
	bool _GameEngineInitialized = false;

	long long _StartTimeStamp = 0;
	long long _FrameTimeStamp = 0;
	long _FrameCount = 0;
	float _CyclesPerMilliSeconds = 0.f;
	float _FrameTime = 0.f;
	float _ElapsedTime = 0.f;
	float _AverageFPS = 0.f;
	float _FrameFPS = 0.f;

	ScreenPoint _ScreenSize;

	std::unique_ptr<RendererInterface> _RIPtr;
	
	GameEngine _GameEngine;
};

