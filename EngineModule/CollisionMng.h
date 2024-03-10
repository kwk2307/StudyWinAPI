#pragma once
class CollisionMng
{

public:
	CollisionMng() = default;

public:
	void Update(float InDeltaSeconds);

	std::function< const std::vector<std::shared_ptr<Object>>& (UINT)> _FuncPtr;

private:
	// Collider끼리 충돌이 되는지 확인하는 검사 테이블 필요
	UINT _CheckTable[(int)ObjectType::End];

	// Collider 들을 담아 놓은 테이블 필요 
	std::vector<Collider*> _Colliders;
};

