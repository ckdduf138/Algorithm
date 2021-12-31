// PerfectMaze.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "PerfectMaze.h"
#include "time.h"
#include <vector>
#include <stack>

using namespace std;

#define MAX_LOADSTRING 100

#define RECT_Start_X 300
#define RECT_Start_Y 50
#define RECT_Width 15
#define RECT_Height 15
#define Wall 1
#define Road 0
#define RED 2

// 전역 함수;
void maze_dfs(int curr_x, int curr_y);          // 미로 DFS

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HWND g_hWnd;                                    // 현재 윈도우
DWORD WINAPI Maze(LPVOID lpParam);              // Maze 쓰레드                    
bool is_Thread_Running = false;                 // 미로 쓰레드가 실행중인지 체크

// direct
int dx[4] = { 2,0,-2,0 };           
int dy[4] = { 0,2,0,-2 };
int crush_dx[4] = { 1,0,-1,0 };
int crush_dy[4] = { 0,1,0,-1 };

// maze vector
vector<vector<int>> maze(31, vector<int>(31));
vector<vector<bool>> visted(31, vector<bool>(31));

// brush pen
HPEN WallPen = CreatePen(0, 0, RGB(153, 153, 255));
HBRUSH WallBrush = CreateSolidBrush(RGB(153,153,255));

HPEN RoadPen = CreatePen(0, 0, RGB(192, 192, 192));
HBRUSH RoadBrush = CreateSolidBrush(RGB(192, 192, 192));

HPEN RedPen = CreatePen(0, 0, RGB(255, 0, 0));
HBRUSH RedBrush = CreateSolidBrush(RGB(255, 0, 0));

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
    LoadStringW(hInstance, IDC_PERFECTMAZE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PERFECTMAZE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PERFECTMAZE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PERFECTMAZE);
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
   g_hWnd = hWnd;
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {

        //초기 미로 생성
        for (int i = 0; i < 31; i++)
        {
            for (int j = 0; j < 31; j++)
            {
                if (i % 2 == 0 && j % 2 == 0) {
                    maze[i][j] = Wall;
                }
                else if (i % 2 == 0 && j % 2 == 1) {
                    maze[i][j] = Wall;
                }
                else if (i % 2 == 1 && j % 2 == 0) {
                    maze[i][j] = Wall;
                }
                else {
                    maze[i][j] = Road;
                }
            }
        }
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
        // 이미 쓰레드가 실행중이면 break
        if (is_Thread_Running == true) break;

        // maze visted vector 초기화
        for (int i = 0; i < 31; i++)
        {
            for (int j = 0; j < 31; j++)
            {
                maze[i][j] = 0;
                visted[i][j] = 0;
            }
        }

        //초기 미로 생성
        for (int i = 0; i < 31; i++)
        {
            for (int j = 0; j < 31; j++)
            {
                if (i % 2 == 0 && j % 2 == 0) {
                    maze[i][j] = Wall;
                }
                else if (i % 2 == 0 && j % 2 == 1) {
                    maze[i][j] = Wall;
                }
                else if (i % 2 == 1 && j % 2 == 0) {
                    maze[i][j] = Wall;
                }
                else {
                    maze[i][j] = Road;
                }
            }
        }

        InvalidateRect(hWnd, NULL, false);

        // 미로 쓰레드 생성
        CreateThread(NULL, 0, Maze, NULL, 0, NULL);

    }
    break;
    case WM_PAINT:
        {

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            for (int i = 0; i < 31; i++)
            {
                for (int j = 0; j < 31; j++)
                {
                    if (maze[i][j] == Wall) {
                        SelectObject(hdc, WallPen);
                        SelectObject(hdc, WallBrush);
                    }
                    else if(maze[i][j] == Road) {
                        SelectObject(hdc, RoadPen);
                        SelectObject(hdc, RoadBrush);
                    }
                    else {
                        SelectObject(hdc, RedPen);
                        SelectObject(hdc, RedBrush);
                        maze[i][j] = Road;
                    }

                    RECT rect = { RECT_Start_X + (RECT_Width * i),RECT_Start_Y + (RECT_Width * j),
                                  rect.left + RECT_Width,rect.top + RECT_Width };

                    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
                }
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

// 미로 셍성 쓰레드
DWORD WINAPI Maze(LPVOID lpParam)
{
    // 랜덤
    srand((unsigned int)time(NULL));

    // 쓰레드 실행중
    is_Thread_Running = true;
    
    HDC hdc = GetDC(g_hWnd);

    int rand_length, rand_width;

    // 랜덤으로 위치 설정
    do {
        rand_length = rand() % 31;
        rand_width = rand() % 31;
    } while (rand_length % 2 == 0 || rand_width % 2 == 0);

    RECT rect = { RECT_Start_X + (RECT_Width * rand_length),RECT_Start_Y + (RECT_Width * rand_width),
          rect.left + RECT_Width,rect.top + RECT_Width };

    // 초기 위치 나타내기
    for (int time = 0; time < 10; time++)
    {
        if (time % 2 == 0) {
            SelectObject(hdc, RedPen);
            SelectObject(hdc, RedBrush);
        }
        else {
            SelectObject(hdc, RoadPen);
            SelectObject(hdc, RoadBrush);
        }
        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
        Sleep(200);
    }


    // 랜덤으로 생성한 초기 X Y visted 체크
    visted[rand_length][rand_width] = true;

    maze_dfs(rand_length, rand_width);

    // 쓰레드 종료
    is_Thread_Running = false;

    ExitThread(0);
    return 0;
}

// 미로 DFS
void maze_dfs(int curr_x, int curr_y) {
    
    // 현재 위치 방문 체크
    visted[curr_x][curr_y] = true;

    vector<int> random(4, -1); // { 0, 1 , 2, 3} 랜덤 배치

    for (int i = 0; i < 4; i++) {
        while (1) {

            int num = rand() % 4;
            auto it = find(random.begin(), random.end(), num);

            if (it == random.end()) {
                random[i] = num;
                break;
            }
        }
    }

    // 랜덤으로 상하좌우 위치 서치
    for (int dir : random) {
        int nx = curr_x + dx[dir];
        int ny = curr_y + dy[dir];

        // Maze 이탈 조건 
        if (nx < 0 || nx >= 31 || ny < 0 || ny >= 31)	continue;
        if (visted[nx][ny])							    continue;

        // 이탈 하지 않음
        visted[nx][ny] = true;

        // 현재 위치 RED 표시
        maze[curr_x + crush_dx[dir]][curr_y + crush_dy[dir]] = RED;
        InvalidateRect(g_hWnd, NULL, false);
        Sleep(50);
        maze[nx][ny] = RED;
        InvalidateRect(g_hWnd, NULL, false);
        Sleep(50);

        maze_dfs(nx, ny);
    }
}