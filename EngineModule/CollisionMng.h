#pragma once
class CollisionMng:
	public CollisionMngInterface
{

public:
	CollisionMng() = default;

public:
	void Init(const SceneMngInterface* InSceneMng);

	virtual void Update(float InDeltaSeconds) override;
	virtual void CheckGroup(ObjectType InLeft, ObjectType InRight) override;

private:
	void CollisionEvent(ObjectType InLeft, ObjectType InRight);

private:
	const SceneMngInterface* _SceneMng;

	// Collider���� �浹�� �Ǵ��� Ȯ���ϴ� �˻� ���̺� �ʿ�
	UINT _CheckTable[(int)ObjectType::End];

	// Collider ���� ��� ���� ���̺� �ʿ� 
	std::vector<Collider*> _Colliders;
};

