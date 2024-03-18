#pragma once

class Object;

class Collider
{
public:
	Collider(Object& InOwner);
	~Collider();
public:
	const Object& GetOwner() const { return _Owner; }

	UINT GetID() const { return _ID; }

	void OnCollision(const Collider& InOther);
	void BeginCollision(const Collider& InOther);
	void EndCollision(const Collider& InOther);

	const Vector3& GetPos() const { return _Pos; }
	void SetPos(const Vector3 InPos) { _Pos = InPos; }

	const Vector3& GetScale() const { return _Scale; }
	void SetScale(const Vector3 InScale) { _Scale = InScale; }

private:

	static UINT _NextID;
	UINT _ID;
	Object& _Owner;

	Vector3 _Pos;
	Vector3 _Scale;
};


