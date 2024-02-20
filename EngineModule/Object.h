#pragma once
enum class ObjectType
{
	Default,
	Camera,
	Player
};

struct ObjectInfo {
	ObjectType type;
	std::string name;
	TransformComponent transform;
	// 추가적인 정보는 json 데이터 형식으로 
	// 저장해둠 
	std::string data = "";
};

class Object
{
public:
	Object() = delete;
	Object(const ObjectInfo& Info);

public:
	virtual void Update(float InDeltaSeconds);
	virtual void Render();
	
	const TransformComponent& GetTransform() const { return _Transform; }

	const std::string& GetName() const { return _Name; }
	std::size_t GetMeshKey() const { return _Meshkey; }



private:
	TransformComponent _Transform;
	ObjectType _ObjectType;
	bool _IsVisible = true;
	std::size_t _Hash = MathUtil::InvalidHash;
	std::string _Name;
	std::size_t _Meshkey = MathUtil::InvalidHash;

private:
	//void DrawMesh(const Mesh& InMesh, const )
};

