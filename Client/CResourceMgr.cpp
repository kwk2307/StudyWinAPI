#include "pch.h"
#include "CResourceMgr.h"
#include "CPathMgr.h"

#include "CRes.h"
#include "CTexture.h"

CResourceMgr::CResourceMgr()
{
}

CResourceMgr::~CResourceMgr()
{
	/*map<wstring, CRes*>::iterator iter = m_mRes.begin();
	for (; iter != m_mRes.end(); ++iter) {
		delete iter->second;
	}*/
	Safe_Erase_Map(m_mRes);
}


CTexture* CResourceMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FIndTexture(_strKey);
	if (pTex != nullptr) {
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += _strRelativePath;
	
	pTex = new CTexture;

	pTex->Load(strFilePath);

	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mRes.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResourceMgr::FIndTexture(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mRes.find(_strKey);

	if (iter == m_mRes.end()) {

		return nullptr;
	}

	return (CTexture*)iter->second;
}
