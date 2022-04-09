#include<Windows.h>

CONST CHAR g_szClassName[] = "My Window Class";
//g		- global
//sz	- string zero

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) ����������� ������ ����:
	WNDCLASSEX wc; //wc - window class | ex - extended
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); //�������� ��������� 'wc'
	//��������������� ���� ��������� 'wc'
	wc.cbSize = sizeof(WNDCLASSEX); //������� cb -��� count bytes
	wc.cbClsExtra = 0; //�������������� ������ ��� ������ ����
	wc.cbWndExtra = 0; //�������������� ������ ��� ������ ����.
	wc.lpfnWndProc = WndProc; //������ ��������� ���� ��� ������� ������
	wc.style = 0;	//����� ����, ���������� ��� �������������� ��������.
					//����� ��������� ������ ������� �� ������ ����
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));	//������, ������������ � ������ �����
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));	//������, ������������ � ������ ��������� (IconSmall)
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));	
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL; //ID ���� ����, ���� ���� ������� ��� ID �������, ���� ���� ��������. NULL - ������ ���� �����������
	wc.lpszClassName = g_szClassName;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	
	//2) �������� ����:
	HWND hwnd = CreateWindowEx
	(
		NULL,			//Ex-style - ����������� ����� ���� (extended)
		g_szClassName,	//��� ������ ����
		"Main window",	//��������� ����
		WS_OVERLAPPEDWINDOW,			//����� ����. � �������� ���� ���������� ����� ������ WS_OVERLAPPEDWINDOW
		CW_USEDEFAULT, CW_USEDEFAULT,	//��������� ����
		CW_USEDEFAULT, CW_USEDEFAULT,	//������ ����
		NULL,			//������������ ���� NULL
		NULL,			//ID ���� ����, ���� ��� �������,��� ID �������, ���� ���� ��������.
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Info", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); //������ ����� �����������
	UpdateWindow(hwnd); //���������� ����

	//3) ������ ����� ���������:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) //GetMessage() ����� ��������� �� ������� ��������� �������� ������.
	{
		TranslateMessage(&msg);	//����������� ��������� virtual-key � ���������� ���������. ���������� ��������� ������������ � ������� ��������� �������� ������.
		DispatchMessage(&msg);	//���������� ��������� � ��������� ����
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:   //����� ��������� �������� ���� (������, ����, ������ � �.�.)
		//��� ������ ��������� WM_INITDIALOG � ���������� ����
		//��� ��������� ������������ ���� ��� - ��� �������� ����.
		break;
	case WM_COMMAND: break;
	case WM_CLOSE:
		//�������� ��������� DestroyWindow ������ ����
		if (MessageBox(hwnd, "Are you sure you want to close the window?", "Close the window", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY: 
		PostQuitMessage(0); //�������� ��������� � ����������� ������
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
