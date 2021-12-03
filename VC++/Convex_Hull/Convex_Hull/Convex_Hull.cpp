// Convex_Hull.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Convex_Hull.h"
#include "time.h"
#include <stack>
#include <algorithm>

using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 전역 함수
void Center_Screen(HWND window, DWORD style, DWORD exStyle);
DWORD WINAPI Convex_Hull(LPVOID lpParam);

struct pos
{
    long long x, y;
};

pos arr[100];
pos last_point;
stack<pos> s;
stack<pos> temp;
bool Convex_flag = false;
bool is_Thread_Running = false;
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CONVEXHULL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONVEXHULL));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CONVEXHULL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CONVEXHULL);
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

long long ccw(pos a, pos b, pos c)
{
    return (a.x * b.y + b.x * c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x);
}

bool cmp1(const pos& a, const pos& b)
{
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool cmp2(pos a, pos b) {
    return ccw(arr[0], a, b) > 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_GETMINMAXINFO: // 윈도우 크기 고정
    {
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 1200;
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 800;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 1200;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 800;
    }
    break;
    case WM_CREATE:
    {

        srand((unsigned int)time(NULL));

        Center_Screen(hWnd, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

    }
    break;

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
    case WM_LBUTTONDOWN:
    {
        if (is_Thread_Running == true) break;
        g_hWnd = hWnd;
        HDC hdc = GetDC(hWnd);
        InvalidateRect(hWnd, NULL, true);

        while (!s.empty()) s.pop();
        while (!temp.empty()) temp.pop();

        for (int idx = 0; idx < 100; idx++)
        {
            int x = (rand() % 1000) + 50;
            int y = (rand() % 600) + 50;
            arr[idx].x = x;
            arr[idx].y = y;
        }

        sort(arr, arr + 100, cmp1);
        stable_sort(arr + 1, arr + 100, cmp2);

        s.push(arr[0]);
        s.push(arr[1]);

        CreateThread(NULL, 0, Convex_Hull, NULL, 0, NULL);
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            HBRUSH POINT = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
            SelectObject(hdc, POINT);


            for (int idx = 0; idx < 100; idx++)
            {
                Ellipse(hdc, arr[idx].x - 3, arr[idx].y - 3, arr[idx].x + 3, arr[idx].y + 3);
            }

            HPEN Pen = CreatePen(0, 3, RGB(64, 224, 208));
            SelectObject(hdc, Pen);
            temp = s;

            bool flag = false;

            while (!temp.empty())
            {
                pos point = temp.top();

                if (flag)
                {
                    LineTo(hdc, point.x, point.y);
                }

                flag = true;
                temp.pop();
                MoveToEx(hdc, point.x, point.y, NULL);
            }

            EndPaint(hWnd, &ps);
        }
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

// Window 화면 가운데 위치로 옮기는 함수
void Center_Screen(HWND window, DWORD style, DWORD exStyle)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    RECT clientRect; GetClientRect(window, &clientRect);
    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;
    SetWindowPos(window, NULL, screenWidth / 2 - clientWidth / 2, screenHeight / 2 - clientHeight / 2 - 40, clientWidth, clientHeight, 0);
}

// 볼록 껍질
DWORD WINAPI Convex_Hull(LPVOID lpParam)
{
    HDC hdc = GetDC(g_hWnd);
    
    is_Thread_Running = true;

    for (int idx = 2; idx < 100; idx++) {
        while (s.size() > 1) {
            pos second = s.top();
            s.pop();
            pos first = s.top();

            if (ccw(first, second, arr[idx]) > 0) {
                s.push(second);
                break;
            }
        }
        s.push(arr[idx]);
        last_point = arr[idx];

        InvalidateRect(g_hWnd, NULL, true);
        Sleep(100);

    }

    HPEN Pen = CreatePen(0, 3, RGB(64, 224, 208));
    SelectObject(hdc, Pen);
    MoveToEx(hdc, last_point.x, last_point.y, NULL);
    LineTo(hdc, arr[0].x, arr[0].y);

    is_Thread_Running = false;

    ExitThread(0);
    return 0;
}
