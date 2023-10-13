#pragma once

// 싱글톤 패턴
// 해당 클래스로 만들어질 수 있는 객체의 개수를 한개로 제한
// extern 키워드 -> 어디서든 접근할 수 있지만 생성을 제한할 수는 없다. 

class CCore
{
	//정적 맴버함수는 this 가 없다.

	//정적 변수 종류
	// 1. 함수 안에 : 데이터 영역에 저장됨. 함수에 호출과 상관없이 존재함
	// 2. 파일 안에 : 데이터 영역에 저장됨. 그 파일 안에서만 호출가능. 전역변수와 다른점은 파일안에서만 이름이 다르면됨
	// 3. 클래스 안에 : 데이터 영역에 저장됨. 클래스가 선언되고 해제되는 것과 상관없이 존재함. 하지만 클래스 내부에서만 접근 가능함

// 클래스의 주소를 동적할당해서 데이터 영역에 있는 정적 맴버변수에 접근하는 방식
//private:
//	static CCore* g_pCore;
//public:
//	static CCore* GetInstance() {
//		 
//		// 최초 호출 됐을 경우
//		if (g_pCore == nullptr) {
//
//			g_pCore = new CCore;
//		}
//		
//		// 2번 이상 호출된 경우 
//		return g_pCore;
//	}
//
//	static void Release(){
//		if (g_pCore != nullptr) {
//
//			delete g_pCore;
//			g_pCore = nullptr;
//		}
//	}


// 객체 자체가 데이터 영역에 올라가는 경우
// 주소 값을 통해 클래스 내부에 접근 가능 
// 데이터 해제를 신경써줄 필요가 없음 프로그램이 종료될 때 같이 종료되기 때문
//public:
	//static const CCore* GetInstance() {
	//	static CCore core;
	//	return &core;
	//}
	// 

	//비슷하게 쓰이는 코드가 많으니까 매크로로 미리 선언해둔다.
	SINGLE(CCore)

private:
	HWND m_hWnd;			//메인 윈도우 핸들
	POINT m_ptResolution;	//메인 윈도우 해상도
	HDC m_hDC;				//Device Context 핸들러

	HBITMAP m_bitmap;		//미리 그릴 비트맵
	HDC m_memhDC;			//새 비트맵의 Device Context 

public:
	int init(HWND _hWnd, POINT _ptResolution);
	HWND getHWND();
	void progress();

private:
	void update();
	void render();
};
