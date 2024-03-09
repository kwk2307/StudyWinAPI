#pragma once
class CollisionMng
{

private:
	CollisionMng();
	~CollisionMng();

public:
	void Update();

	using FuncPtr = const std::vector<std::unique_ptr<Object>>& (SceneMng::*)(UINT InType) const;
	
	FuncPtr _FuncPtr;

private:
	// Collider끼리 충돌이 되는지 확인하는 검사 테이블 필요
	UINT _CheckTable[(int)ObjectType::End];

	// Collider 들을 담아 놓은 테이블 필요 
	std::vector<Collider*> _Colliders;
};

