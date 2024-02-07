#pragma once
class Renderer
{
public:
	Renderer(RendererInterface* RI);

	void Tick();

	float GetFrameFPS() const { return _FrameFPS; }
	float GetElapsedTime() const { return _ElapsedTime; }

	// 성능 측정
	std::function<float()> _PerformanceInitFunc;
	std::function<INT64()> _PerformanceMeasureFunc;
	//std::function<void(InputManager&)> _InputBindingFunc;

private:
	// 초기화 점검 변수
	bool _PerformanceCheckInitialized = false;
	bool _RendererInitialized = false;
	bool _GameEngineInitialized = false;
	bool _TickEnabled = false;
	bool _AllInitialized = false;

	void PreUpdate();
	void PostUpdate();

	long long _StartTimeStamp = 0;
	long long _FrameTimeStamp = 0;
	long _FrameCount = 0;
	float _CyclesPerMilliSeconds = 0.f;
	float _FrameTime = 0.f;
	float _ElapsedTime = 0.f;
	float _AverageFPS = 0.f;
	float _FrameFPS = 0.f;
};

