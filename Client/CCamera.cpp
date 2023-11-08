#include "pch.h"
#include "CCamera.h"

#include "CCore.h"
#include "CObject.h"

CCamera::CCamera():
	m_pParentObj(nullptr),
	m_vCameraPos{}
{
}

CCamera::~CCamera() 
{
}

void CCamera::init()
{
}

void CCamera::update()
{
	if (m_pParentObj != nullptr) {
		m_vCameraPos = m_pParentObj->GetPos();
	}
}

Vec2 CCamera::GetCalcPos()
{
	POINT Resolution = CCore::GetInstance()->getResolution();
	return Vec2(m_vCameraPos.x - Resolution.x/2, m_vCameraPos.y - Resolution.y/2);
}

void CCamera::MoveCamera()
{

}

