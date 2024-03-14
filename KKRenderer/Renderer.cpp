#include "Precompiled.h"
#include "Renderer.h"

Renderer::Renderer(RendererInterface* RI) :
	_RIPtr(RI)
{
	_GameEngine = new GameEngine(new SceneMng(), new CollisionMng());
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

	//inputManger ������Ʈ 
	InputManager::GetInstanc().Update();

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

	g.Update(InDeltaSeconds);
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
	const Matrix4 viewMatrix = mainCamera.GetViewMatrix();

	for (UINT Type = 0; Type < (UINT)ObjectType::End; ++Type) {
		for (auto it = g.GetSceneMng().GetCurrentScene(Type).begin();
			it != g.GetSceneMng().GetCurrentScene(Type).end(); ++it) {

			const Object& object = *(*it);
			if (!object.HasMesh() || !object.IsVisible()) {
				continue;
			}

			const Mesh& mesh = g.GetSceneMng().GetMesh(object.GetMeshKey());
			const TransformComponent& transform = object.GetTransform();
			const Texture& texture = g.GetSceneMng().GetTexture(object.GetTextureKey());

			//����� * �𵨸� ��� 
			Matrix4 finalMatrix = viewMatrix * transform.GetModelingMatrix();

			DrawMesh(mesh, finalMatrix, texture);
		}
	}

}
//
void Renderer::DrawMesh(const Mesh& InMesh, const Matrix4& InMatrix , const Texture& InTexture)
{
	size_t vertexCount = InMesh.GetVertices().size();
	size_t indexCount = InMesh.GetIndices().size();
	size_t triangleCount = indexCount / 3;

	// �������� ����� ���� ���ۿ� �ε��� ���۷� ��ȯ
	std::vector<Vertex> vertices(vertexCount);
	std::vector<size_t> indices(InMesh.GetIndices());

	for (size_t vi = 0; vi < vertexCount; ++vi) {
		
		vertices[vi].Position = Vector4(InMesh.GetVertices()[vi]);
		if (InMesh.HasUV())
		{
			vertices[vi].UV = InMesh.GetUVs()[vi];
		}
	}

	for (Vertex& v : vertices) {
		v.Position = InMatrix * v.Position;
	}
	for (int ti = 0; ti < triangleCount; ++ti) {
		int bi0 = ti * 3, bi1 = ti * 3 + 1, bi2 = ti * 3 + 2;
		std::vector<Vertex> tvs = { vertices[indices[bi0]] , vertices[indices[bi1]] , vertices[indices[bi2]] };

		size_t triangles = tvs.size() / 3;
		for (size_t ti = 0; ti < triangles; ++ti)
		{
			size_t si = ti * 3;
			std::vector<Vertex> sub(tvs.begin() + si, tvs.begin() + si + 3);
			DrawTriangle(sub,InTexture);
		}
	}
}

void Renderer::DrawTriangle(std::vector<Vertex>& InVertices, const Texture& InTexture)
{
	GameEngine& g = GetGameEngine();
	auto& r = GetRenderer();

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
				
				r.DrawPoint(fragment, InTexture.GetSample(targetUV));
			}
		}
	}
}

