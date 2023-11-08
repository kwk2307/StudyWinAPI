#include "pch.h"
#include "CAnimation.h"

#include "CTexture.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CCamera.h"

#include "CObject.h"

CAnimation::CAnimation() :
	m_pAnimator(nullptr),
	m_fTime(0.f),
	m_pTex(nullptr),
	m_strName(),
	m_iCnt(0)
{
}

CAnimation::~CAnimation()
{
	
}

void CAnimation::Create(const wstring& _str, CTexture* _pTex, Vec2 _vLT, Vec2 _vSize, UINT _cnt)
{
	m_strName = _str;
	m_pTex = _pTex;
	
	for (UINT i = 0; i < _cnt; ++i) {
		m_vecFrameInfo.push_back({ 0.2f, {_vLT.x + (i * _vSize.x) ,_vLT.y},_vSize });
	}
}

void CAnimation::update()
{
	float fDT = CTimeMgr::GetInstance()->GetfDT();

	m_fTime += fDT;
		
	if (m_vecFrameInfo[m_iCnt].fDuration < m_fTime) {
		m_fTime -= m_vecFrameInfo[m_iCnt].fDuration;
		
		m_iCnt++;
		if (m_iCnt == m_vecFrameInfo.size()) {
			m_iCnt = 0;
		}
	}
}

void CAnimation::render(HDC _dc)
{
	Vec2 vRenderPos = m_pAnimator->GetOwner()->GetPos() - CCamera::GetInstance()->GetCalcPos();

	TransparentBlt(_dc,
		(int)(vRenderPos.x - (m_vecFrameInfo[m_iCnt].m_vSize.x / 2.f)),
		(int)(vRenderPos.y - (m_vecFrameInfo[m_iCnt].m_vSize.y / 2.f)),
		(int)m_vecFrameInfo[m_iCnt].m_vSize.x,
		(int)m_vecFrameInfo[m_iCnt].m_vSize.y,
		m_pTex->GetDC(),
		(int)m_vecFrameInfo[m_iCnt].m_vLT.x,
		(int)m_vecFrameInfo[m_iCnt].m_vLT.y,
		(int)m_vecFrameInfo[m_iCnt].m_vSize.x,
		(int)m_vecFrameInfo[m_iCnt].m_vSize.y,
		RGB(255, 0, 255)
	);
}
