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
	// Collider���� �浹�� �Ǵ��� Ȯ���ϴ� �˻� ���̺� �ʿ�
	UINT _CheckTable[(int)ObjectType::End];

	// Collider ���� ��� ���� ���̺� �ʿ� 
	std::vector<Collider*> _Colliders;
};

