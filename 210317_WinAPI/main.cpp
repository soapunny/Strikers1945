// main.cpp
#include "config.h"
#include "MainGame.h"

// ��������
// �ν��Ͻ� : ��ü �޸𸮻� �����ϴ� ��ü
HINSTANCE g_hInstance;		// ���α׷� �ν��Ͻ� �ڵ�
HWND g_hWnd;				// ������ �ڵ�
LPSTR g_lpszClass = (LPSTR)TEXT("�������� ����");
MainGame g_mainGame;

void SetClientTect(HWND hWnd, int width, int height);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	g_hInstance = _hInstance;

	// �����츦 �����ϱ� ���� �⺻����
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	wndClass.cbClsExtra = 2068;
	wndClass.cbWndExtra = 2068;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hIconSm = LoadIcon(wndClass.hInstance, MAKEINTRESOURCE(IDI_SHIELD));

	// ������ Ŭ���� ���
	RegisterClassEx(&wndClass);

	// ������ ����
	g_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		50, 50, WINSIZE_X, WINSIZE_Y,
		NULL, NULL, g_hInstance, NULL);

	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);

	SetClientTect(g_hWnd, WINSIZE_X, WINSIZE_Y);

	TimerManager::GetSingleton()->Init();
	
	if (FAILED(g_mainGame.Init()))
	{
		MessageBox(g_hWnd, "���� ���� �ʱ�ȭ ����!!", "���", MB_OK);
		//return 0;
	}

	// �޽��� ť�� �ִ� �޽��� ó��
	MSG message;
	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))	// �޼����� ������ �޼��� ó��
		{
			if (message.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else											// �޼��ð� ������ game ������Ʈ
		{
			//htimer�� �ƴ϶� cpu timer�� ����ϱ� ����
			TimerManager::GetSingleton()->Update();
			g_mainGame.Update();
			
			g_mainGame.Render();
		}
	}

	/*while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}*/

	g_mainGame.Release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}

//0,0 �κп� �ִ� �޴��ٰ� ������� ������ ���� ���� ���� ��ġ
void SetClientTect(HWND hWnd, int width, int height)
{
	RECT crt;
	DWORD style, exStyle;

	SetRect(&crt, 0, 0, width, height);											//crt�� ���õǾ��ִ�(����ϰ� ����) rect ���� ����
	style = GetWindowLong(hWnd, GWL_STYLE);										//���� �ִ� ������ ��Ÿ���� �����´�
	exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);									//(���� ������ ���� �ʿ��� ����)
	AdjustWindowRectEx(&crt, style, GetMenu(hWnd) != NULL, exStyle);			//���� ��Ÿ�Ͽ� ���缭 rect���� �ٽ� ������ �ִ� �Լ�

	if (style & WS_VSCROLL) crt.right += GetSystemMetrics(SM_CXVSCROLL);		//�����ʿ� ��ũ�� �� ����� �� ũ�⸸ŭ �߰�
	if (style & WS_VSCROLL) crt.bottom += GetSystemMetrics(SM_CXHSCROLL);		//�Ʒ��ʿ� ��ũ�� �� ����� �� ũ�⸸ŭ �߰�

	SetWindowPos(hWnd, NULL, 0, 0, crt.right - crt.left, crt.bottom - crt.top,
		SWP_NOMOVE | SWP_NOZORDER);

}