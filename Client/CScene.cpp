#include "pch.h"
#include "CScene.h"
#include "CObject.h"

CScene::CScene():
	m_VecObjects{}
{
}

CScene::~CScene()
{
}

void CScene::update()
{
	for (int i = 0; i < (INT)ObjectType::END;  ++i) {
		for (int j = 0; j < m_VecObjects[i].size(); ++j) {
			m_VecObjects[i][j]->update();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (int i = 0; i < (INT)ObjectType::END; ++i) {
		for (int j = 0; j < m_VecObjects[i].size(); ++j) {
			m_VecObjects[i][j]->render();
		}
	}
}

