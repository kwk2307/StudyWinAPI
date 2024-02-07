#include "Precompiled.h"
#include "Renderer.h"
#include "WindowsUtil.h"
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

    Renderer Instance(new WindowsRenderer());
    ScreenPoint defScreenSize(800, 600);

    WindowsPlayer::gOnResizeFunc = [&Instance](const ScreenPoint& InNewScreenSize) {
        if (InNewScreenSize.HasZero()) {
            return;
        }
        Instance.OnResize(InNewScreenSize);
    };

    Instance._PerformanceInitFunc = WindowsUtil::GetCyclesPerMilliSeconds;
    Instance._PerformanceMeasureFunc = WindowsUtil::GetCurrentTimeStamp;

    // 애플리케이션 초기화를 수행합니다:
    if (!WindowsPlayer::InitInstance (nCmdShow, defScreenSize))
    {
        return FALSE;
    }

    // AccelerTable 등록 
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KKRENDERER));
    
    static float previousTimer = 0.f;
    static float updatePeriod = 500.f;
    while (WindowsPlayer::Tick()) {
        // 
        Instance.Tick();

        float currentTime = Instance.GetElapsedTime();
        if (currentTime - previousTimer > updatePeriod)
        {
            //float frameFPS = Instance.GetFrameFPS();
            float AverFPS = Instance.GetAverageFPS();
            WindowsPlayer::SetWindowsStatTitle(AverFPS);
            previousTimer = currentTime;
        }
    }

    WindowsPlayer::Destroy();
    return 0;
}

