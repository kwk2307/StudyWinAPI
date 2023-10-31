#pragma once


//싱글톤 패턴 매크로로 미리 정의
#define SINGLE(type) public: \
						static type* GetInstance() {\
						static type mgr; \
						return &mgr;}\
					 private: \
						type();\
						~type();

#define KEYCHECK(key,state) CKeyMgr::GetInstance()->GetKeyState(key) == state

#define KEYCHKCK_TAP(key) KEYCHECK(key,KEY_STATE::TAP)
#define KEYCHKCK_HOLD(key) KEYCHECK(key,KEY_STATE::HOLD)
#define KEYCHKCK_AWAY(key) KEYCHECK(key,KEY_STATE::AWAY)
#define KEYCHKCK_NONE(key) KEYCHECK(key,KEY_STATE::NONE)

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

enum class BrushType {
	HOLLOW,
	END,
};

enum class PenType {
	RED,
	GREEN,
	BLUE,
	END
};

enum class EventType {
	SCENECHANGE,
	CREATEOBJECT,
	DELETEOBJECT,
	END,
};
