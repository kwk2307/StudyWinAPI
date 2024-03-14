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
	_SceneMng->GetCurrentScene((UINT)InLeft);
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
