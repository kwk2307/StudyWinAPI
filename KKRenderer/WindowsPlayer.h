#pragma once

namespace WindowsPlayer {
	static HINSTANCE gInstance;
	static HWND gHandle;

    static const TCHAR* gClassName = _T("SOFTRENDERER_PLAYER");
    static TCHAR gTitle[64];
    static TCHAR gPlayTitle[128];

    // ���� ���� 
    INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

    //
    //  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
    //
    //  �뵵: �� â�� �޽����� ó���մϴ�.
    //
    //  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
    //  WM_PAINT    - �� â�� �׸��ϴ�.
    //  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
    //
    //
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�:
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
    //  �Լ�: MyRegisterClass()
    //
    //  �뵵: â Ŭ������ ����մϴ�.
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
    //   �Լ�: InitInstance(HINSTANCE, int)
    //
    //   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
    //
    //   �ּ�:
    //
    //        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
    //        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
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

    // ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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