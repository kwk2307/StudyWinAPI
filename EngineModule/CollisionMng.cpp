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
			//�� �浹ü ��� Collider�� �����ϰ� �ڽ��� �ڽſ��� ��ģ���� �ƴϴ�. 

			Collider& LeftCol = *(vecLeft[i].get()->GetCollider());
			Collider& RightCol = *(vecRight[j].get()->GetCollider());

			bool LeftDead = LeftCol.GetOwner().GetState();
			bool RightDead = RightCol.GetOwner().GetState();

			// �ʿ��� �˻� ����
			COLLIDER_ID tid;
			tid.LeftID = LeftCol.GetID();
			tid.RightID = RightCol.GetID();

			iter = m_mColliderTable.find(tid.llID);

			if (iter == m_mColliderTable.end()) {
				m_mColliderTable.insert(std::make_pair(tid.llID, false));
				iter = m_mColliderTable.find(tid.llID);
			}

			//�浹�� ���� ��
			if (isCollision(*(vecLeft[i].get()), *(vecRight[i].get()))) {
				//ó������ �浹 ��
				if (!iter->second) {
					//�Ѵ� ��� ���� ��
					if (!(LeftDead || RightDead))
					{
						LeftCol.BeginCollision(RightCol);
						RightCol.BeginCollision(LeftCol);
						iter->second = true;
					}
				}
				//�̹� �浹 ��
				else {
					//�Ѵ� ��� ���� ��
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
			//�浹�� �ȵ�
			else {
				if (!iter->second) {
					//Do Nothing
				}
				//�̹� �浹 ��
				else {
					LeftCol.EndCollision(RightCol);
					RightCol.EndCollision(LeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionMng::isCollision(const Object& InLeftObj,const Object& InRightObj)
{	
	Matrix4 LeftModelingMatrix = InLeftObj.GetTransform().GetModelingMatrix();
	Mesh LeftMesh = _SceneMng->GetMesh(InLeftObj.GetMeshKey());
	Vector3 LeftExtent = LeftMesh.GetBoxBound().GetExtent();

	std::vector<Vector3> LeftNormals = { Vector3(LeftExtent.X,0.f,0.f),Vector3(0.f,LeftExtent.Y,0.f) ,Vector3(0.f,0.f,LeftExtent.Z) };
	for (Vector3& vec : LeftNormals) {
		vec = LeftModelingMatrix * vec;
	}

	std::vector<Vector3>& LeftVertices = LeftMesh.GetVertices();
	for (Vector3& vec : LeftVertices) {
		vec = LeftModelingMatrix * vec;
	}
	//std::vector<size_t>& LeftIndices = LeftMesh.GetIndices();

	//std::vector<Vector3> LeftNormals;
	//for (int i = 0; i < LeftMesh.GetIndices().size() / 3; ++i) {
	//	Vector3 vec = (LeftVertices[LeftIndices[i * 3 + 1]] - LeftVertices[LeftIndices[i * 3]]).Cross(LeftVertices[LeftIndices[i * 3 + 2]] - LeftVertices[LeftIndices[i * 3]]);
	//	std::vector<Vector3>::iterator iter = std::find(LeftNormals.begin(), LeftNormals.end(), vec);

	//	if (iter == LeftNormals.end()) {
	//		LeftNormals.push_back(vec);
	//	}
	//}

	Matrix4 RightModelingMatrix = InRightObj.GetTransform().GetModelingMatrix();
	Mesh RightMesh = _SceneMng->GetMesh(InRightObj.GetMeshKey());
	Vector3 RightExtent = RightMesh.GetBoxBound().GetExtent();

	std::vector<Vector3> RightNormals = { Vector3(RightExtent.X,0.f,0.f),Vector3(0.f,RightExtent.Y,0.f) ,Vector3(0.f,0.f,RightExtent.Z) };
	for (Vector3& vec : RightNormals) {
		vec = RightModelingMatrix * vec;
	}

	std::vector<Vector3>& RightVertices = RightMesh.GetVertices();
	for (Vector3& vec : RightVertices) {
		vec = RightModelingMatrix * vec;
	}

	//std::vector<size_t>& RightIndices = RightMesh.GetIndices();

	//std::vector<Vector3> RightNormals;
	//for (int i = 0; i < RightMesh.GetIndices().size() / 3; ++i) {
	//	Vector3 vec = (RightVertices[RightIndices[i * 3 + 1]] - RightVertices[RightIndices[i * 3]]).Cross(RightVertices[RightIndices[i * 3 + 2]] - RightVertices[RightIndices[i * 3]]);
	//	
	//	std::vector<Vector3>::iterator iter = std::find(RightNormals.begin(), RightNormals.end(), vec);
	//	if (iter == RightNormals.end()) {
	//		RightNormals.push_back(vec);
	//	}
	//}

	std::vector<Vector3> EdgeNormals;
	for (const auto& LeftNormal : LeftNormals) {
		for (const auto& RightNormal : RightNormals) {
			Vector3 vec = LeftNormal.Cross(RightNormal);
			EdgeNormals.push_back(vec);
		}
	}

	for (const auto& normal : LeftNormals) {
		Interval projection1 = project(LeftVertices, normal);
		Interval projection2 = project(RightVertices, normal);
		if (!overlap(projection1, projection2))
			return false;
	}

	for (const auto& normal : RightNormals) {
		Interval projection1 = project(LeftVertices, normal);
		Interval projection2 = project(RightVertices, normal);
		if (!overlap(projection1, projection2))
			return false;
	}
	for (const auto& normal : EdgeNormals) {
		Interval projection1 = project(LeftVertices, normal);
		Interval projection2 = project(RightVertices, normal);
		if (!overlap(projection1, projection2))
			return false;
	}


	return true;
}

Interval CollisionMng::project(const std::vector<Vector3>& poly, const Vector3& axis)
{
	double min = INFINITY, max = -INFINITY;
	for (const auto& vertex : poly) {
		
		double projection = vertex.X * axis.X + vertex.Y * axis.Y + vertex.Z * axis.Z;
		if (projection < min) min = projection;
		if (projection > max) max = projection;
	}
	return { min, max };
}

bool CollisionMng::overlap(Interval a, Interval  b) {
	return !(a.max < b.min || b.max < a.min);
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
