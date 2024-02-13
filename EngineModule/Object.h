#pragma once
class Object
{
public:
	void Update(float InDeltaSeconds);
	void Render();

private:
	TransformComponent _Transform;
};

