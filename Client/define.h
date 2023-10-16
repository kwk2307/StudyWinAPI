#pragma once


//�̱��� ���� ��ũ�η� �̸� ����
#define SINGLE(type) public: \
						static type* GetInstance() {\
						static type mgr; \
						return &mgr;}\
					 private: \
						type();\
						~type();

enum class SceneType {
	STARTSCENE,
	STAGE01,
	STAGE02,

	END,
};

enum class ObjectType {
	DEFAULT,
	PLAYER,
	BLOCK,
	MONSETER,

	END = 32,
};