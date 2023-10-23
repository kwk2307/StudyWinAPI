#include "pch.h"
#include "CPathMgr.h"

void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);
}

CPathMgr::CPathMgr()
	:m_szContentPath{}
{}
CPathMgr::~CPathMgr()
{}

