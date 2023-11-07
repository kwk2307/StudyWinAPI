#pragma once

class CObject;

void CreateObject(CObject* _ptObj, ObjectType _eType);

void DeleteObject(CObject* _ptObj);

void ChangeScene(SceneType _eType);

template<typename T>
void Safe_Erase_Vecter(vector<T>& _vec) {
	for (int i = 0; i < _vec.size(); ++i) {
		if (_vec[i] != nullptr) {
			delete _vec[i];
		}
	}
	_vec.clear();
}

template<typename T1, typename T2>
void Safe_Erase_Map(map<T1, T2>& _map) {
	typename map<T1, T2>::iterator iter;
	for (iter = _map.begin(); iter != _map.end(); iter++)
	{
		delete iter->second;
	}
}