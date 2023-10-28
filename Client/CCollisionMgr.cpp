#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr():
	m_arrCheck{}
{

}
CCollisionMgr::~CCollisionMgr() {

}

void CCollisionMgr::init()
{
}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)ObjectType::END; ++iRow) {
		for (UINT iCol = iRow; iCol < (UINT)ObjectType::END; ++iCol) {
			if (m_arrCheck[iRow] & (1 << iCol)) {
				CollisionEvent((ObjectType)iRow, (ObjectType)iCol);
			}
		}
	}
}


bool CCollisionMgr::isCollision(CCollider* _ptLeftCol, CCollider* _ptRightCol)
{
	Vec2 vLeftPos = _ptLeftCol->GetFinalPos();
	Vec2 vLeftSacle = _ptLeftCol->GetScale();

	Vec2 vRightPos = _ptRightCol->GetFinalPos();
	Vec2 vRightSacle = _ptRightCol->GetScale();


	if ((abs(vRightPos.x - vLeftPos.x) < (vRightSacle.x + vLeftSacle.x) / 2.f) &&
		(abs(vRightPos.y - vLeftPos.y) < (vRightSacle.y + vLeftSacle.y) / 2.f)) {
		return true;
	}

	return false;
}

void CCollisionMgr::CollisionEvent(ObjectType _eLeft, ObjectType _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurrentScene();
	
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<LONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i) {
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;
		for (size_t j = 0; i < vecRight.size(); ++j) {
			if (vecRight[j]->GetCollider() == nullptr
				|| vecLeft[i] == vecRight[j])
				continue;
			//두 충돌체 모두 Collider가 존재하고 자신이 자신에게 겹친것이 아니다. 

			CCollider* ptLeftCol =  vecLeft[i]->GetCollider();
			CCollider* ptRightCol = vecRight[j]->GetCollider();

			// 맵에서 검사 해줌
			COLLIDER_ID tid;			
			tid.iLeftID = ptLeftCol->GetID();
			tid.iRightID = ptRightCol->GetID();

			iter = m_mColliderTable.find(tid.llID);

			if (iter == m_mColliderTable.end()) {
				m_mColliderTable.insert(make_pair(tid.llID, false));
				iter = m_mColliderTable.find(tid.llID);
			}

			if (isCollision(ptLeftCol, ptRightCol)) {
				if (!iter->second) {
					ptLeftCol->BeginCollision(ptRightCol);
					ptRightCol->BeginCollision(ptLeftCol);
					iter->second = true;
				}
				else {
					ptLeftCol->OnCollision(ptRightCol);
					ptRightCol->OnCollision(ptLeftCol);
				}
			}
			else {
				if (iter->second) {
					ptLeftCol->EndCollision(ptRightCol);
					ptRightCol->EndCollision(ptLeftCol);
					iter->second = false;
				}
			}
		}
	}
}


void CCollisionMgr::CheckGroup(ObjectType _eLeft, ObjectType _eRight)
{

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow) {
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	
	if (m_arrCheck[iRow] & (1 << iCol)) {
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else {
		m_arrCheck[iRow] |= (1 << iCol);
	}

}



