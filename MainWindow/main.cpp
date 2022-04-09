#include<Windows.h>

CONST CHAR g_szClassName[] = "My Window Class";
//g		- global
//sz	- string zero

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wc; //wc - window class | ex - extended
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); //зануляем экземпляр 'wc'
	//Иниициализируем поля структуры 'wc'
	wc.cbSize = sizeof(WNDCLASSEX); //префикс cb -это count bytes
	wc.cbClsExtra = 0; //дополнительная память для класса окна
	wc.cbWndExtra = 0; //дополнительная память для самого окна.
	wc.lpfnWndProc = WndProc; //задаем процедуру окна для данного класса
	wc.style = 0;	//стиль окна, определяет его дополнительные свойства.
					//набор возможных стилей зависит от класса окна
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));	//иконка, отображаемая в панели задач
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));	//Иконка, отображаемая в строке заголовка (IconSmall)
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));	
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL; //ID меню окна, если окно главное ИЛИ ID ресурса, если окно дочернее. NULL - значит меню отсутствует
	wc.lpszClassName = g_szClassName;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	
	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,			//Ex-style - расширенный стиль окна (extended)
		g_szClassName,	//имя класса окна
		"Main window",	//заголовок окна
		WS_OVERLAPPEDWINDOW,			//Стиль окна. У главного окна приложения стиль всегда WS_OVERLAPPEDWINDOW
		CW_USEDEFAULT, CW_USEDEFAULT,	//Положение окна
		CW_USEDEFAULT, CW_USEDEFAULT,	//размер окна
		NULL,			//Родительское окно NULL
		NULL,			//ID меню окна, если оно главное,или ID ресурса, если окно дочернее.
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Info", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); //Задаем режим отображения
	UpdateWindow(hwnd); //Прорисовка окна

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) //GetMessage() берет сообщение из очереди сообщений текущего потока.
	{
		TranslateMessage(&msg);	//Преобразует сообщения virtual-key в символьные сообщения. Символьные сообщения отправляются в очередь сообщений текущего потока.
		DispatchMessage(&msg);	//Отправляет сообщение в процедуру окна
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:   //Здесь создаются элементы окна (Кнопки, меню, значки и т.д.)
		//Это аналог сообщения WM_INITDIALOG в диалоговом окне
		//Это сообщение отрабатывает один раз - при создании окна.
		break;
	case WM_COMMAND: break;
	case WM_CLOSE:
		//Посылает сообщение DestroyWindow своему окну
		if (MessageBox(hwnd, "Are you sure you want to close the window?", "Close the window", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY: 
		PostQuitMessage(0); //Посылает сообщение о прекращении работы
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
