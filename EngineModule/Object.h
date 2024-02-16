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
	// �߰����� ������ data�� ������ ��
	std::string data = "";
};

class Object
{
public:
	Object();
public:
	void Update(float InDeltaSeconds);
	void Render();

private:
	//TransformComponent _Transform;
	ObjectType _ObjectType;
};


