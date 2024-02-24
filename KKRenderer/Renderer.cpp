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
	GetRenderer().Clear(Color::White);

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
	// �÷��̾�� Ű�Է��� �޾� �����δ� 

	// ī�޶�� �÷��̾��� x ��ġ�� �°� �����δ�. 
}

void Renderer::LateUpdate(float InDeltaSeconds)
{

}

void Renderer::Render()
{

	GameEngine& g = GetGameEngine();
	auto& r = GetRenderer();
	auto& mainCamera = g.GetSceneMng().GetCamera();

	//ViewMatrix ����
	const Matrix4 viewMatrix = mainCamera.get()->GetViewMatrix();

	for (auto it = g.GetSceneMng().GetCurrentScene().begin();
		it != g.GetSceneMng().GetCurrentScene().end(); ++it) {

		const Object& object = *(*it);
		if (!object.HasMesh() || !object.IsVisible()) {
			continue;
		}

		const Mesh& mesh = g.GetMesh(object.GetMeshKey());
		const TransformComponent& transform = object.GetTransform();


		//����� * �𵨸� ��� 
		Matrix4 finalMatrix = viewMatrix* transform
	
	}

	std::vector<Vertex> Test;

	Test.push_back(Vertex(Vector4(100.f, 100.f, 0.f, 0.f)));
	Test.push_back(Vertex(Vector4(200.f, 100.f, 0.f, 0.f)));
	Test.push_back(Vertex(Vector4(200.f, 200.f, 0.f, 0.f)));

	DrawTriangle(Test);
}

void Renderer::DrawTriangle(std::vector<Vertex>& InVertices)
{
	GameEngine& g = GetGameEngine();
	auto& r = GetRenderer();
	auto& mainCamera = g.GetSceneMng().GetCamera();

	// 1. �ﰢ���� �׷��� ������ ���Ѵ�.
	Vector2 minPos(MathUtil::Min3(InVertices[0].Position.X, InVertices[1].Position.X, InVertices[2].Position.X), MathUtil::Min3(InVertices[0].Position.Y, InVertices[1].Position.Y, InVertices[2].Position.Y));
	Vector2 maxPos(MathUtil::Max3(InVertices[0].Position.X, InVertices[1].Position.X, InVertices[2].Position.X), MathUtil::Max3(InVertices[0].Position.Y, InVertices[1].Position.Y, InVertices[2].Position.Y));

	// ���� �߽� ��ǥ�� ���� ���� ��ȯ 
	Vector2 u = InVertices[1].Position.ToVector2() - InVertices[0].Position.ToVector2();
	Vector2 v = InVertices[2].Position.ToVector2() - InVertices[0].Position.ToVector2();

	// ���� �и� �� ( uu * vv - uv * uv )
	float udotv = u.Dot(v);
	float vdotv = v.Dot(v);
	float udotu = u.Dot(u);
	float denominator = udotv * udotv - vdotv * udotu;

	// ��ȭ �ﰢ�� ����.
	if (denominator == 0.f)
	{
		return;
	}

	float invDenominator = 1.f / denominator;
	ScreenPoint lowerLeftPoint = ScreenPoint::ToScreenCoordinate(_ScreenSize, minPos);
	ScreenPoint upperRightPoint = ScreenPoint::ToScreenCoordinate(_ScreenSize, maxPos);
	

	// �� �������� ������ �� ������ z��
	float invZ0 = 1.f / InVertices[0].Position.W;
	float invZ1 = 1.f / InVertices[1].Position.W;
	float invZ2 = 1.f / InVertices[2].Position.W;

	for (int x = lowerLeftPoint.X; x <= upperRightPoint.X; ++x)
	{
		for (int y = upperRightPoint.Y; y <= lowerLeftPoint.Y; ++y)
		{
			ScreenPoint fragment = ScreenPoint(x, y);
			Vector2 pointToTest = fragment.ToCartesianCoordinate(_ScreenSize);
			Vector2 w = pointToTest - InVertices[0].Position.ToVector2();
			float wdotu = w.Dot(u);
			float wdotv = w.Dot(v);

			float s = (wdotv * udotv - wdotu * vdotv) * invDenominator;
			float t = (wdotu * udotv - wdotv * udotu) * invDenominator;
			float oneMinusST = 1.f - s - t;

			// ���������� ����� ���� �и�
			float z = invZ0 * oneMinusST + invZ1 * s + invZ2 * t;
			float invZ = 1.f / z;

			//���� �߽� ��ǥ�� �� �� 1�� 0 ���̿� �ִ� == �׷����ϴ� �ȼ��̴�.
			if (((s >= 0.f) && (s <= 1.f)) && ((t >= 0.f) && (t <= 1.f)) && ((oneMinusST >= 0.f) && (oneMinusST <= 1.f)))
			{
				// ���� ���������� UV ��ǥ
				Vector2 targetUV = (InVertices[0].UV * oneMinusST * invZ0 + InVertices[1].UV * s * invZ1 + InVertices[2].UV * t * invZ2) * invZ;
				r.DrawPoint(fragment,Color::Blue);
			}
		}
	}
}

