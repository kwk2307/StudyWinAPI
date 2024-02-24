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


//왼손 좌표계를 기준으로 저장함
class Object
{
public:
	Object() = delete;
	Object(const ObjectInfo& Info);

public:
	virtual void Update(float InDeltaSeconds);

	const TransformComponent& GetTransform() const { return _Transform; }
	bool IsVisible() const { return _IsVisible; }

	const ObjectType& GetType() const { return _ObjectType; }
	const std::string& GetName() const { return _Name; }
	std::size_t GetMeshKey() const { return _Meshkey; }
	bool HasMesh() const { return _Meshkey != MathUtil::InvalidHash; }

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

