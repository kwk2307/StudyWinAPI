#include "Precompiled.h"


void CollisionMng::Init(const SceneMngInterface* InSceneMng)
{
	_SceneMng = InSceneMng;
}

void CollisionMng::Update(float InDeltaSeconds)
{
	for (UINT Row = 0; Row < (UINT)ObjectType::End; ++Row) {
		for (UINT Col = 0; Col < (UINT)ObjectType::End; ++Col) {
			if (_CheckTable[Row] & (1 << Col)) {
				CollisionEvent((ObjectType)Row, (ObjectType)Col);
			}
		}
	}
}

void CollisionMng::CollisionEvent(ObjectType InLeft, ObjectType InRight)
{
	const std::vector<std::shared_ptr<Object>> vecLeft = _SceneMng->GetCurrentScene((UINT)InLeft);
	const std::vector<std::shared_ptr<Object>> vecRight = _SceneMng->GetCurrentScene((UINT)InRight);
	std::map<LONGLONG, bool>::iterator iter;
	//for (size_t i = 0; i < vecLeft.size(); ++i) {
	//	if (vecLeft[i].get()->GetCollider() == nullptr)
	//		continue;
	//	for (size_t j = 0; j < vecRight.size(); ++j) {
	//		if (vecRight[j]->GetCollider() == nullptr || vecLeft[i] == vecRight[j])
	//			continue;
	//		//두 충돌체 모두 Collider가 존재하고 자신이 자신에게 겹친것이 아니다. 

	//		Collider* LeftCol = vecLeft[i].get()->GetCollider();
	//		Collider* RightCol = vecRight[j].get()->GetCollider();

	//		bool bLeftDead = LeftCol->GetOwner()->GetDead();
	//		bool bRightDead = RightCol->GetOwner()->GetDead();

	//		// 맵에서 검사 해줌
	//		COLLIDER_ID tid;
	//		tid.LeftID = ptLeftCol->GetID();
	//		tid.RightID = ptRightCol->GetID();

	//		iter = m_mColliderTable.find(tid.llID);

	//		if (iter == m_mColliderTable.end()) {
	//			m_mColliderTable.insert(std::make_pair(tid.llID, false));
	//			iter = m_mColliderTable.find(tid.llID);
	//		}

	//		//충돌이 됐을 때
	//		if (isCollision(ptLeftCol, ptRightCol)) {
	//			//처음으로 충돌 됨
	//			if (!iter->second) {
	//				//둘다 살아 있을 때
	//				if (!(bLeftDead || bRightDead))
	//				{
	//					ptLeftCol->BeginCollision(ptRightCol);
	//					ptRightCol->BeginCollision(ptLeftCol);
	//					iter->second = true;
	//				}
	//			}
	//			//이미 충돌 중
	//			else {
	//				//둘다 살아 있을 때
	//				if (!(bLeftDead || bRightDead)) {
	//					ptLeftCol->OnCollision(ptRightCol);
	//					ptRightCol->OnCollision(ptLeftCol);
	//				}
	//				else {
	//					ptLeftCol->EndCollision(ptRightCol);
	//					ptRightCol->EndCollision(ptLeftCol);
	//					iter->second = false;
	//				}
	//			}
	//		}
	//		//충돌이 안됨
	//		else {
	//			if (!iter->second) {
	//				//Do Nothing
	//			}
	//			//이미 충돌 중
	//			else {
	//				ptLeftCol->EndCollision(ptRightCol);
	//				ptRightCol->EndCollision(ptLeftCol);
	//				iter->second = false;
	//			}
	//		}
	//	}
	//}
}

bool CollisionMng::isCollision(Collider* InLeftCol, Collider* InRightCol)
{
	
	// 충돌 처리 방식 결정해야함...
	// AABB ??
	// SAT  ?

	// 안그래도 느린데 
	return false;

}

void CollisionMng::CheckGroup(ObjectType InLeft, ObjectType InRight)
{
	UINT iRow = (UINT)InLeft;
	UINT iCol = (UINT)InRight;

	if (iCol < iRow) {
		iRow = (UINT)InRight;
		iCol = (UINT)InLeft;
	}

	if (_CheckTable[iRow] & (1 << iCol)) {
		_CheckTable[iRow] &= ~(1 << iCol);
	}
	else {
		_CheckTable[iRow] |= (1 << iCol);
	}
}
