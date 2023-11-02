#include "pch.h"
#include "CScene.h"
#include "CObject.h"

void CScene::update()
{
	for (int i = 0; i < (INT)ObjectType::END;  ++i) {
		for (int j = 0; j < m_VecObjects[i].size(); ++j) {
			m_VecObjects[i][j]->update();

		}
	}
}

void CScene::finalupdate()
{
	for (int i = 0; i < (INT)ObjectType::END; ++i) {
		for (int j = 0; j < m_VecObjects[i].size(); ++j) {
			m_VecObjects[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (int i = 0; i < (INT)ObjectType::END; ++i) {
		iter = m_VecObjects[i].begin();
		for (; iter !=  m_VecObjects[i].end();) {
			if ((*iter)->GetDead()) {
				// 동적 할당된 메모리를 해제 해줌
				delete ((*iter));
				// 벡터에서 값을 제거 해줌
				iter = m_VecObjects[i].erase(iter);
			}
			else {
				(*iter)->render(_dc);
				iter++;
			}
		}
	}
}

CScene::CScene() :
	m_VecObjects{}
{
}

CScene::~CScene()
{
}
