#include "pch.h"
#include "CAnimation.h"

CAnimation::CAnimation() :
	m_fTime(0.f),
	m_pTex(nullptr),
	m_strName()
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Create(const wstring& _str, CRes* _pRes, Vec2 _vLT, Vec2 _vSize, UINT _cnt)
{
	m_strName = _str;
	m_pTex = _pRes;
	
	for (UINT i = 0; i < _cnt; ++i) {
		m_vecFrameInfo.push_back({ 0.1f, {_vLT.x + (i * _vSize.x) ,_vLT.y},_vSize });
	}
}