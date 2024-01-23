

#include "framework.h"
#include "Precompiled.h"
#include "WindowsPlayer.h"

#define MAX_LOADSTRING 100

// 전역 변수:
//HINSTANCE hInst;                                // 현재 인스턴스입니다.
//WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
//WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WindowsPlayer::MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!WindowsPlayer::InitInstance (nCmdShow))
    {
        return FALSE;
    }

    // AccelTable 등록 
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KKRENDERER));

    while (WindowsPlayer::Tick()) {

    }

    WindowsPlayer::Destroy();
    return 0;
}

