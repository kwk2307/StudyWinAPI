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
	// 추가적인 정보는 data에 저장해 둠
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


