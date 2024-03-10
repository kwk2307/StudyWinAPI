#pragma once
class CollisionMng
{

public:
	CollisionMng() = default;

public:
	void Update(float InDeltaSeconds);
	void CheckGroup(ObjectType InLeft, ObjectType InRight);

private:
	void CollisionEvent(ObjectType InLeft, ObjectType InRight);

public:
	std::function< const std::vector<std::shared_ptr<Object>>& (UINT)> _FuncPtr;

private:
	// Collider���� �浹�� �Ǵ��� Ȯ���ϴ� �˻� ���̺� �ʿ�
	UINT _CheckTable[(int)ObjectType::End];

	// Collider ���� ��� ���� ���̺� �ʿ� 
	std::vector<Collider*> _Colliders;
};

