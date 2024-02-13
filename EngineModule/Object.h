#pragma once
enum class ObjectType
{
	Default,
	Camera,
	Player
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


