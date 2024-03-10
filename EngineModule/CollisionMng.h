#pragma once
class CollisionMng
{

public:
	CollisionMng() = default;

public:
	void Update(float InDeltaSeconds);

	std::function< const std::vector<std::shared_ptr<Object>>& (UINT)> _FuncPtr;

private:
	// Collider���� �浹�� �Ǵ��� Ȯ���ϴ� �˻� ���̺� �ʿ�
	UINT _CheckTable[(int)ObjectType::End];

	// Collider ���� ��� ���� ���̺� �ʿ� 
	std::vector<Collider*> _Colliders;
};

