#pragma once

class CObject;

void CreateObject(CObject* _ptObj, ObjectType _eType);

void DeleteObject(CObject* _ptObj);

void ChangeScene(SceneType _eType);

template<class T>
void Safe_Erase_Vecter(vector<T>& _vec) {
	for (int i = 0; i < _vec.size(); ++i) {
		if (_vec[i] != nullptr) {
			delete _vec[i];
		}
	}
	_vec.clear();
}