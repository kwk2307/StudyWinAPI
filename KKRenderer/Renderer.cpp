#include "Precompiled.h"
#include "Renderer.h"

Renderer::Renderer(RendererInterface* RI) :
	_RIPtr(RI)
{

}

void Renderer::Tick()
{
	// �����ս� ī���� �ʱ�ȭ.
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

	// ��ũ�� ũ�� Ȯ��
	if (_ScreenSize.HasZero())
	{
		return;
	}

	// ����Ʈ ������ �ʱ�ȭ.
	if (!_RendererInitialized)
	{
		_RendererInitialized = GetRenderer().Init(_ScreenSize);
		if (!_RendererInitialized)
		{
			assert(false);
			return;
		}
	}

	// ���� ���� �ʱ�ȭ
	_GameEngineInitialized = GetGameEngine().IsInitailzed();
	if (!_GameEngineInitialized) {

		_GameEngineInitialized = GetGameEngine().Init();

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
	// ���� ���� ����.
	_FrameTimeStamp = _PerformanceMeasureFunc();
	if (_FrameCount == 0)
	{
		_StartTimeStamp = _FrameTimeStamp;
	}

	// ��� �����.
	GetRenderer().Clear(Color::Black);

}

void Renderer::PostUpdate()
{
	GetRenderer().EndFrame();

	// ���� ���� ������.
	_FrameCount++;
	INT64 currentTimeStamp = _PerformanceMeasureFunc();
	INT64 frameCycles = currentTimeStamp - _FrameTimeStamp;
	INT64 elapsedCycles = currentTimeStamp - _StartTimeStamp;
	_FrameTime = frameCycles / _CyclesPerMilliSeconds;
	_ElapsedTime = elapsedCycles / _CyclesPerMilliSeconds;
	_FrameFPS = _FrameTime == 0.f ? 0.f : 1000.f / _FrameTime;
	_AverageFPS = _ElapsedTime == 0.f ? 0.f : 1000.f / _ElapsedTime * _FrameCount;
}

void Renderer::LoadScene(std::string& SceneName)
{
	const GameEngine& g = GetGameEngine();
}

void Renderer::Update(float InDeltaSeconds)
{
	GameEngine& g = GetGameEngine();

	for (auto it = g.GetSceneMng().GetCurrentScene().begin();
		it != g.GetSceneMng().GetCurrentScene().end(); ++it) {

		Object& object = *(*it);
		object.Update(InDeltaSeconds);
	}
	//�÷��̾�� Ű�Է��� �޾� �����δ� 
}

void Renderer::LateUpdate(float InDeltaSeconds)
{

}

void Renderer::Render()
{
	auto& r = GetRenderer();
	GameEngine& g = GetGameEngine();

	

	for (auto it = g.GetSceneMng().GetCurrentScene().begin();
		it != g.GetSceneMng().GetCurrentScene().end(); ++it) {

		const Object& object = *(*it);
		const TransformComponent& transform = object.GetTransform();
		if (!object.HasMesh() || !object.IsVisible()) {
			continue;
		}

	
	}
}

