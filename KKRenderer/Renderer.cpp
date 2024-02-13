#include "Precompiled.h"
#include "Renderer.h"

Renderer::Renderer(RendererInterface* RI) :_RIPtr(RI)
{}

void Renderer::Tick()
{
	// 퍼포먼스 카운터 초기화.
	if (!_PerformanceCheckInitialized)
	{
		if (_PerformanceInitFunc && _PerformanceMeasureFunc)
		{
			_CyclesPerMilliSeconds = _PerformanceInitFunc();
			_PerformanceCheckInitialized = true;
		}
		else
		{
			assert(false);
			return;
		}
	}

	// 스크린 크기 확인
	if (_ScreenSize.HasZero())
	{
		return;
	}

	// 소프트 렌더러 초기화.
	if (!_RendererInitialized)
	{
		_RendererInitialized = GetRenderer().Init(_ScreenSize);
		if (!_RendererInitialized)
		{
			assert(false);
			return;
		}
	}

	// 게임 엔진 초기화
	_GameEngineInitialized = _GameEngine.IsInitailzed();
	if (!_GameEngineInitialized) {

		_GameEngineInitialized = _GameEngine.Init(_CurrentScene);
		if (!_GameEngineInitialized)
		{
			assert(false);
			return;
		}
	}


	assert(_RIPtr != nullptr && GetRenderer().IsInitialized() && !_ScreenSize.HasZero());

	if (_PerformanceCheckInitialized && _RendererInitialized && _GameEngineInitialized) {

		PreUpdate();

		Update(_FrameTime / 1000.f);
		Render();

		PostUpdate();
	}
}

void Renderer::OnResize(const ScreenPoint& InScreeSize)
{
	_ScreenSize = InScreeSize;
}

void Renderer::PreUpdate()
{
	// 성능 측정 시작.
	_FrameTimeStamp = _PerformanceMeasureFunc();
	if (_FrameCount == 0)
	{
		_StartTimeStamp = _FrameTimeStamp;
	}

	// 배경 지우기.
	GetRenderer().Clear(Color::Black);

}

void Renderer::PostUpdate()
{
	GetRenderer().EndFrame();

	// 성능 측정 마무리.
	_FrameCount++;
	INT64 currentTimeStamp = _PerformanceMeasureFunc();
	INT64 frameCycles = currentTimeStamp - _FrameTimeStamp;
	INT64 elapsedCycles = currentTimeStamp - _StartTimeStamp;
	_FrameTime = frameCycles / _CyclesPerMilliSeconds;
	_ElapsedTime = elapsedCycles / _CyclesPerMilliSeconds;
	_FrameFPS = _FrameTime == 0.f ? 0.f : 1000.f / _FrameTime;
	_AverageFPS = _ElapsedTime == 0.f ? 0.f : 1000.f / _ElapsedTime * _FrameCount;
}

void Renderer::LoadScene()
{
}

void Renderer::Update(float InDeltaSeconds)
{
	GameEngine& g = GetGameEngine();
	

	
}

void Renderer::LateUpdate(float InDeltaSeconds)
{
}

void Renderer::Render()
{
}

