#pragma once

namespace WindowsPlayer {
	static HINSTANCE gInstance;
	static HWND gHandle;

    static const TCHAR* gClassName = _T("SOFTRENDERER_PLAYER");
    static TCHAR gTitle[64];
    static TCHAR gPlayTitle[128];

    // 전방 선언 
    INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

    //
    //  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
    //
    //  용도: 주 창의 메시지를 처리합니다.
    //
    //  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
    //  WM_PAINT    - 주 창을 그립니다.
    //  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
    //
    //
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(gInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }

    //
    //  함수: MyRegisterClass()
    //
    //  용도: 창 클래스를 등록합니다.
    //
    ATOM MyRegisterClass(HINSTANCE hInstance)
    {
        gInstance = hInstance;

        WNDCLASSEXW wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = gInstance;
        wcex.hIcon = LoadIcon(gInstance, MAKEINTRESOURCE(IDI_KKRENDERER));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KKRENDERER);
        wcex.lpszClassName = gClassName;
        wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        return RegisterClassExW(&wcex);
    }

    //
    //   함수: InitInstance(HINSTANCE, int)
    //
    //   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
    //
    //   주석:
    //
    //        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
    //        주 프로그램 창을 만든 다음 표시합니다.
    //
    BOOL InitInstance(int nCmdShow,const ScreenPoint& InDefaultScreenSize)
    {
        RECT rect;
        rect.left = 0;
        rect.top = 0;
        rect.right = InDefaultScreenSize.X - 1;
        rect.bottom = InDefaultScreenSize.Y - 1;
        ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
        int WindowWidth = rect.right - rect.left + 1;
        int WindowHeight = rect.bottom - rect.top + 1;

        gHandle = ::CreateWindow(gClassName, gTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
            (GetSystemMetrics(SM_CXFULLSCREEN) - WindowWidth) / 2, (GetSystemMetrics(SM_CYFULLSCREEN) - WindowHeight) / 2, WindowWidth, WindowHeight,
            NULL, NULL, gInstance, NULL);

        if (!gHandle)
        {
            return FALSE;
        }

        ShowWindow(gHandle, nCmdShow);
        UpdateWindow(gHandle);

        return TRUE;
    }

    // 정보 대화 상자의 메시지 처리기입니다.
    INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        UNREFERENCED_PARAMETER(lParam);
        switch (message)
        {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }
        return (INT_PTR)FALSE;
    }

    bool Tick() {
        MSG msg;
        ZeroMemory(&msg, sizeof(msg));

        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                return false;
        }

        return true;
    }

    void Destroy()
    {
        DestroyWindow(gHandle);
    }
}