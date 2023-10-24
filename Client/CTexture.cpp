#include "pch.h"
#include "CTexture.h"

#include "CCore.h"

CTexture::CTexture()
	: m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
}

void CTexture::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	
	m_dc = CreateCompatibleDC(CCore::GetInstance()->getHDC());

	DeleteObject(SelectObject(m_dc, m_hBit));
	
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
	
	assert(m_hBit);
}
