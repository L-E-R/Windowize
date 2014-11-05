// MyWin.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include <shellapi.h> //ShellExecute


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];           // The title bar text
int cmdShow=0;								
HWND hcWnd; HWND hWnd;
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    MyDlgProc(HWND,UINT,WPARAM,LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	cmdShow=nCmdShow;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MYWIN, szWindowClass, MAX_LOADSTRING);
	//MyRegisterClass(hInstance);

	// Perform application initialization:
	/*if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}*/
	hInst=hInstance;
	DialogBox(hInst,(LPCTSTR)IDD_MYDLG,NULL,(DLGPROC)MyDlgProc);
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MYWIN);//加载加速键表
	
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MYWIN);//加载图标
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_MYWIN;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   SetMenu(hWnd,NULL);
   
   //CWindow myWindow;
   //SetWindowLong(hWnd,GWL_STYLE,GetWindowLong(hWnd,GWL_STYLE)|~WS_CAPTION);
   //SetWindowPos(hWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   SetTimer(hWnd, 1, 1000, NULL);
   char buf[MAX_PATH]={0};
   GetModuleFileName(NULL,buf,MAX_PATH);//获得当前路径
   //char *p=buf;
  // int len=strlen(buf);
   //for(int i=len-1;i>=0;i--)
   //{
	//   if(p[i]=='\\')
	//   {
	//	   memset(&p[i+1],0,len-i-1);
	////	   strcpy(&p[i+1],"Test.exe");
	//	   break;
	//   }
   //}
  // ShellExecute(hWnd,"open",buf,NULL,NULL,SW_SHOW); //启动目标程序
   Sleep(300);
   
   //= ::FindWindow(NULL, "计算器");//通过窗口名找到目标程序窗口句柄
   hcWnd = ::FindWindow(NULL, "屏幕演示程序");
   //while (!hcWnd) {
	//   Sleep(5000);
	  // hcWnd = ::FindWindow(NULL, "计算器");
   //}
	::SetParent(hcWnd,hWnd);//绑架(设置目标程序的父窗口为当前窗口)
   

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
// 					{
// 						HWND hcWnd=::FindWindow(NULL,"TestWinPcap");
// 						if(hcWnd)
// 						{
// 							::SetParent(hcWnd,hWnd);
// 						}
// 					}
					
				   break;
				case IDM_MYDLG:
					DialogBox(hInst,(LPCTSTR)IDD_MYDLG,hWnd,(DLGPROC)MyDlgProc);
					break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_TIMER:
			if (!hcWnd) hcWnd = ::FindWindow(NULL, "屏幕演示程序");
			else ::SetParent(hcWnd, hWnd);
			break;
		case WM_DESTROY:
			KillTimer(hWnd, 1);
			PostQuitMessage(0);//退出的时候一定要调用此函数,
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

LRESULT CALLBACK MyDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	switch(message)
	{
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDOK:
				MyRegisterClass(hInst);
				
				// Perform application initialization:
				if (!InitInstance (hInst, cmdShow)) 
				{
					return FALSE;
				}
				//EndDialog(hWnd, wParam);
				break;
			case IDCANCEL:
				EndDialog(hWnd,wParam);
				//DestroyWindow(hWnd);
				return TRUE;
			case IDC_EDIT:
				{
					if(HIWORD(wParam)==EN_CHANGE)
					{
						OutputDebugString("change");
					}
					break;
				}
			}
			
		}
		break;
	case WM_DESTROY:
		//PostQuitMessage(0);//退出的时候一定要调用此函数,
		break;
	/*default:
			return DefWindowProc(hWnd, message, wParam, lParam);*/
	}
	return FALSE;
}
