#include "pch.h"
#include "CBlock.h"

#include "CCollider.h"

CBlock::CBlock()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(30.f, 30.f));

}
CBlock::~CBlock() {

}
void CBlock::update()
{
}

void CBlock::OnCollision(CCollider* _pOther)
{
	DeleteObject(this);
}
