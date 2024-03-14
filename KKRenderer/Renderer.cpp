#include "Precompiled.h"
#include "Renderer.h"

Renderer::Renderer(RendererInterface* RI) :
	_RIPtr(RI)
{
	_GameEngine = new GameEngine(new SceneMng(), new CollisionMng());
}

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
	// 성능 측정 시작.
	_FrameTimeStamp = _PerformanceMeasureFunc();
	if (_FrameCount == 0)
	{
		_StartTimeStamp = _FrameTimeStamp;
	}

	//inputManger 업데이트 
	InputManager::GetInstanc().Update();

	// 배경 지우기.
	GetRenderer().Clear(Color::White);

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
	
	//ViewMatrix 만듦
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

			//뷰행렬 * 모델링 행렬 
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

	// 렌더러가 사용할 정점 버퍼와 인덱스 버퍼로 변환
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

	// 무게 중심 좌표를 위한 벡터 변환 
	Vector2 u = InVertices[1].Position.ToVector2() - InVertices[0].Position.ToVector2();
	Vector2 v = InVertices[2].Position.ToVector2() - InVertices[0].Position.ToVector2();

	// 공통 분모 값 ( uu * vv - uv * uv )
	float udotv = u.Dot(v);
	float vdotv = v.Dot(v);
	float udotu = u.Dot(u);
	float denominator = udotv * udotv - vdotv * udotu;

	// 퇴화 삼각형 판정.
	if (denominator == 0.f)
	{
		return;
	}

	float invDenominator = 1.f / denominator;
	ScreenPoint lowerLeftPoint = ScreenPoint::ToScreenCoordinate(_ScreenSize, minPos);
	ScreenPoint upperRightPoint = ScreenPoint::ToScreenCoordinate(_ScreenSize, maxPos);
	

	// 각 정점마다 보존된 뷰 공간의 z값
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

			// 투영보정에 사용할 공통 분모
			float z = invZ0 * oneMinusST + invZ1 * s + invZ2 * t;
			float invZ = 1.f / z;

			//무게 중심 좌표가 셋 다 1과 0 사이에 있다 == 그려야하는 픽셀이다.
			if (((s >= 0.f) && (s <= 1.f)) && ((t >= 0.f) && (t <= 1.f)) && ((oneMinusST >= 0.f) && (oneMinusST <= 1.f)))
			{
				// 최종 보정보간된 UV 좌표
				Vector2 targetUV = (InVertices[0].UV * oneMinusST * invZ0 + InVertices[1].UV * s * invZ1 + InVertices[2].UV * t * invZ2) * invZ;
				
				r.DrawPoint(fragment, InTexture.GetSample(targetUV));
			}
		}
	}
}

