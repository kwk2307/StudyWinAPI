#pragma once

class Object;

class Collider
{
public:
	Collider(const Object& InOwner);
	~Collider();
public:
	const Object& GetOwner() const { return _Owner; }

private:
	const Object& _Owner;

	Vector3 _Preset;
	Vector3 _Size;
};

