#pragma once


//싱글톤 패턴 매크로로 미리 정의
#define SINGLE(type) public: \
						static type* GetInstance() {\
						static type mgr; \
						return &mgr;}\
					 private: \
						type();\
						~type();