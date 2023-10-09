﻿// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Client.h"
#include "vector"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//wWInMain - 애플리케이션의 main 함수 
//SAL 주석언어 - 매개변수 앞에 변수의 용도를 적어준다.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 실행된 프로세스의 시작 주소
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine, // 실행 시 추가 인자 입력 
                     _In_ int       nCmdShow  // 
)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    // 리소스 뷰의 String Table에서 가져와서 넣어줘라
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    
    //윈도우 정보 등록
    MyRegisterClass(hInstance);

    //윈도우 생성 
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //단축키 테이블 정보 로딩 
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
    // 메세지 큐에서 매세지를 확인할 때 까지 대기 
    // GetMessage 함수는 WM_QUIT 메세지를 입력 받을 경우 False를 반환한다. 
    // 현재 구조는 게임 클라이언트로 작동하기는 부적합하다. 

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        //msg.hwnd 메세지가 발생한 창 
        //각 윈도우가 가지고 있는 Processor 가 처리 해준다. 
        //Processor 의 경우 MyResisterClass 함수에서 등록해준다.
        // wcex.ipfnWinProc <- 이거임 
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

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


struct tObjInfo {
    POINT ptLT = { 500,500 };
    POINT ptRB = { 100,100 };
};

std::vector<tObjInfo> g_vecInfo;

POINT g_ptLT;
POINT g_ptRB;


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
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            // 펜을 만들어서 DC에 지급
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            // 테이블에서 브러쉬를 가져옴
            //HBRUSH hWhiteBrush = GetStockObject()
            
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);

            for (auto info : g_vecInfo) {
                Rectangle(hdc, info.ptLT.x, info.ptLT.y, info.ptRB.x, info.ptRB.y);
            }
            //Rectangle(hdc, g_ptLT.x, g_ptLT.y, g_ptRB.x, g_ptRB.y);
           
            SelectObject(hdc, hDefaultPen);

            DeleteObject(hRedPen);

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:
    {
        // 버튼을 꾹 누르고 있을 때 최초 메세지 처리 이후에 1초 후 메세지 처리가 발생하는 이유는 
        // 윈도우 메세지를 처리하는 방식 때문이다.
        switch (wParam)
        {
        case VK_UP:
            //g_ObjectPos.y -= 10;        
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_DOWN:
            //g_ObjectPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_RIGHT:
            //g_ObjectPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_LEFT:
            //g_ObjectPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case WM_LBUTTONDOWN:
            
            break;
        case 'W':
            break;
        default:
            break;
        }
        break;
    }
    case WM_LBUTTONDOWN:
    {
        //클릭된 마우스 윈도우 좌표 
        //2byte/2byte 해서 총 4byte 
        //비트연산 해서 가져오면된다. 이를 위한 매크로 또한 존재한다.
        //x ,y 좌표 
        g_ptLT.x = LOWORD(lParam);
        g_ptLT.y = HIWORD(lParam);

        break;
    }
    case WM_MOUSEMOVE:
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
        break;

    case WM_LBUTTONUP:
        g_vecInfo.push_back({{g_ptLT.x,g_ptLT.y },{g_ptRB.x,g_ptRB.y}});
        InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default: 
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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
