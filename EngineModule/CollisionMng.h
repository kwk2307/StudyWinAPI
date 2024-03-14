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

	// Collider끼리 충돌이 되는지 확인하는 검사 테이블 필요
	UINT _CheckTable[(int)ObjectType::End];

	// Collider 들을 담아 놓은 테이블 필요 
	std::vector<Collider*> _Colliders;
};

