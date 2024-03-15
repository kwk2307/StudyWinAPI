#pragma once


union COLLIDER_ID {
	struct {
		UINT LeftID;
		UINT RightID;
	};
	LONGLONG llID;
};

class CollisionMng:
	public CollisionMngInterface
{

public:
	CollisionMng() = default;

public:
	void Init(const SceneMngInterface* InSceneMng);

	void Update(float InDeltaSeconds);
	void CheckGroup(ObjectType InLeft, ObjectType InRight);

private:
	void CollisionEvent(ObjectType InLeft, ObjectType InRight);
	bool isCollision(Collider* InLeftCol, Collider* InRightCol);

private:
	const SceneMngInterface* _SceneMng;

	// Collider���� �浹�� �Ǵ��� Ȯ���ϴ� �˻� ���̺� �ʿ�
	UINT _CheckTable[(int)ObjectType::End];
	std::map<LONGLONG, bool> m_mColliderTable;

	// Collider ���� ��� ���� ���̺� �ʿ� 
	std::vector<Collider*> _Colliders;
};

