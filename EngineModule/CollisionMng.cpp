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
	for (size_t i = 0; i < vecLeft.size(); ++i) {
		if (vecLeft[i].get()->GetCollider() == nullptr)
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j) {
			if (vecRight[j]->GetCollider() == nullptr || vecLeft[i] == vecRight[j])
				continue;
			//두 충돌체 모두 Collider가 존재하고 자신이 자신에게 겹친것이 아니다. 

			Collider& LeftCol = *(vecLeft[i].get()->GetCollider());
			Collider& RightCol = *(vecRight[j].get()->GetCollider());

			LeftCol.GetOwner();

			bool LeftDead = LeftCol.GetOwner().GetState();
			bool RightDead = RightCol.GetOwner().GetState();

			// 맵에서 검사 해줌
			COLLIDER_ID tid;
			tid.LeftID = LeftCol.GetID();
			tid.RightID = RightCol.GetID();

			iter = m_mColliderTable.find(tid.llID);

			if (iter == m_mColliderTable.end()) {
				m_mColliderTable.insert(std::make_pair(tid.llID, false));
				iter = m_mColliderTable.find(tid.llID);
			}

			//충돌이 됐을 때
			if (isCollision(LeftCol, RightCol)) {
				//처음으로 충돌 됨
				if (!iter->second) {
					//둘다 살아 있을 때
					if (!(LeftDead || RightDead))
					{
						LeftCol.BeginCollision(RightCol);
						RightCol.BeginCollision(LeftCol);
						iter->second = true;
					}
				}
				//이미 충돌 중
				else {
					//둘다 살아 있을 때
					if (!(LeftDead || RightDead)) {
						LeftCol.OnCollision(RightCol);
						RightCol.OnCollision(LeftCol);
					}
					else {
						LeftCol.EndCollision(RightCol);
						RightCol.EndCollision(LeftCol);
						iter->second = false;
					}
				}
			}
			//충돌이 안됨
			else {
				if (!iter->second) {
					//Do Nothing
				}
				//이미 충돌 중
				else {
					LeftCol.EndCollision(RightCol);
					RightCol.EndCollision(LeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionMng::isCollision(const Collider& InLeftCol,const Collider& InRightCol)
{
	Vector3 LeftPos = InLeftCol.GetPos();
	Vector3 LeftScale = InLeftCol.GetScale();

	Vector3 RightPos = InRightCol.GetPos();
	Vector3 RightScale = InRightCol.GetScale();

	if ((MathUtil::Abs(RightPos.X - LeftPos.X) <= (RightScale.X + LeftScale.X) / 2.f)
		&& (MathUtil::Abs(RightPos.Y - LeftPos.Y) <= (RightScale.Y + LeftScale.Y) / 2.f)
		&& (MathUtil::Abs(RightPos.Z - LeftPos.Z) <= (RightScale.Z + LeftScale.Z) / 2.f)) {

		return true;
	}

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
