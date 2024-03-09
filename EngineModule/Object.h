#pragma once
enum class ObjectType
{
	Default,
	Camera,
	Player,
	Block,
	End
};

struct ObjectInfo {
	ObjectType type;
	std::string name;
	TransformComponent transform;
	
	std::string Mesh;
	std::string Texture;

	// 추가적인 정보는 json 데이터 형식으로 
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
	TransformComponent& GetTransform() { return _Transform; }
	bool IsVisible() const { return _IsVisible; }

	const ObjectType& GetType() const { return _ObjectType; }
	const std::string& GetName() const { return _Name; }
	std::size_t GetMeshKey() const { return _Meshkey; }
	std::size_t GetTextureKey() const { return _Texturekey; }


	bool HasMesh() const { return _Meshkey != MathUtil::InvalidHash; }
	
	void SetMeshKey(size_t InKey) { _Meshkey = InKey; }
	void SetTextureKey(size_t InKey) { _Texturekey = InKey; }

private:
	TransformComponent _Transform;
	ObjectType _ObjectType;
	
	bool _IsVisible = true;
	std::size_t _Hash = MathUtil::InvalidHash;
	std::string _Name;

	std::size_t _Meshkey =  MathUtil::InvalidHash;
	std::size_t _Texturekey = MathUtil::InvalidHash;

private:
	//void DrawMesh(const Mesh& InMesh, const )
};
