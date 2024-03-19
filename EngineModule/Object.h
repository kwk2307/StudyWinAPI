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
	ObjectType type = ObjectType::Default;
	std::string name;
	TransformComponent transform;

	std::string Mesh;
	std::string Texture;

	bool IsCollision = false;
	bool IsAnimator = false;
};

//�޼� ��ǥ�踦 �������� ������
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

	// �������� �Ѱ��ִ� ���� �ƴ� ��� �����ִ� ��(?)
	// Collider ��ü�� cosnt ��� �Լ����� ȣ���� �� ����
	// const Object ��ü �϶��� �� �Լ��� ȣ�� ���� sd
	const Collider* GetCollider() const { return _Collider.get(); }
	Collider* GetCollider() { return _Collider.get(); }

	Animator* GetAnimator() { return _Animator.get(); }

	bool HasMesh() const { return _Meshkey != MathUtil::InvalidHash; }
	
	void SetMeshKey(size_t InKey) { _Meshkey = InKey; }
	void SetTextureKey(size_t InKey) { _Texturekey = InKey; }

	bool GetState() const { return _IsDead; }

public:

	virtual void OnCollision(const Collider& InOther);

	virtual void BeginCollision(const Collider& InOther);

	virtual void EndCollision(const Collider& InOther);

private:
	TransformComponent _Transform;
	ObjectType _ObjectType;
	
	std::unique_ptr<Collider> _Collider = nullptr;
	std::unique_ptr<Animator> _Animator = nullptr;

	bool _IsVisible = true;
	std::size_t _Hash = MathUtil::InvalidHash;
	std::string _Name;

	std::size_t _Meshkey =  MathUtil::InvalidHash;
	std::size_t _Texturekey = MathUtil::InvalidHash;

	bool _IsDead = false;

private:
	//void DrawMesh(const Mesh& InMesh, const )
};
