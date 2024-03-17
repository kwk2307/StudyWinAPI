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
	virtual void Init(const SceneMngInterface* InSceneMng) override;

	virtual void Update(float InDeltaSeconds) override;
	virtual void CheckGroup(ObjectType InLeft, ObjectType InRight) override;

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

