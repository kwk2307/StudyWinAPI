#pragma once

class CCollider;

union COLLIDER_ID {
	struct {
		UINT iLeftID;
		UINT iRightID;
	};
	LONGLONG llID;
};

class CCollisionMgr
{
SINGLE(CCollisionMgr)
private:
	UINT m_arrCheck[(UINT)ObjectType::END];
	map<LONGLONG, bool> m_mColliderTable;

public:

	void init();
	void update();
	void CheckGroup(ObjectType eLeft, ObjectType eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)ObjectType::END); }

private:

	bool isCollision(CCollider* _ptLeftCol, CCollider* _ptRightCol);
	void CollisionEvent(ObjectType _eLeft, ObjectType _eRight);
};

