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

	std::vector<Vector3>& LeftVertices = LeftMesh.GetVertices();
	for (Vector3& vec : LeftVertices) {
		vec = LeftModelingMatrix * vec;
	}
	std::vector<size_t>& LeftIndices = LeftMesh.GetIndices();

	std::vector<Vector3> LeftNormals;
	for (int i = 0; i < LeftMesh.GetIndices().size() / 3.f; ++i) {
		LeftNormals.push_back(
			LeftVertices[LeftIndices[i * 3 + 1]] - LeftVertices[LeftIndices[i * 3]].Cross(LeftVertices[LeftIndices[i * 3 + 1]] - LeftVertices[LeftIndices[i * 3]])
		);
	}

	Matrix4 RightModelingMatrix = InRightObj.GetTransform().GetModelingMatrix();
	Mesh RightMesh = _SceneMng->GetMesh(InRightObj.GetMeshKey());

	std::vector<Vector3>& RightVertices = RightMesh.GetVertices();
	for (Vector3& vec : RightVertices) {
		vec = RightModelingMatrix * vec;
	}
	std::vector<size_t>& RightIndices = RightMesh.GetIndices();

	std::vector<Vector3> RightNormals;
	for (int i = 0; i < RightMesh.GetIndices().size() / 3.f; ++i) {
		RightNormals.push_back(
			RightVertices[RightIndices[i * 3 + 1]] - RightVertices[RightIndices[i * 3]].Cross(RightVertices[RightIndices[i * 3 + 1]] - RightVertices[RightIndices[i * 3]])
		);
	}

	for (const auto& normal : LeftNormals) {
		std::pair projection1 = project(LeftMesh.GetVertices(), normal);
		std::pair projection2 = project(RightMesh.GetVertices(), normal);
		if (!overlap(projection1, projection2))
			return false;
	}

	for (const auto& normal : RightNormals) {
		std::pair<double, double> projection1 = project(LeftMesh.GetVertices(), normal);
		std::pair<double, double> projection2 = project(RightMesh.GetVertices(), normal);
		if (!overlap(projection1, projection2))
			return false;
	}

	return true;
}

//�࿡ ���� �� �ٸ�ü�� max, min ���
std::pair<double,double> project(const std::vector<Vector3>& poly, const Vector3& axis) {
	double min = INFINITY, max = -INFINITY;
	for (const auto& vertex : poly) {
		// �࿡ ������ ����
		double projection = vertex.X * axis.X + vertex.Y * axis.Y + vertex.Z * axis.Z;
		if (projection < min) min = projection;
		if (projection > max) max = projection;
	}
	return { min, max };
}

bool overlap(std::pair<double, double> a, std::pair<double, double> b) {
	return !(a.second < b.first || b.second < a.first);
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
