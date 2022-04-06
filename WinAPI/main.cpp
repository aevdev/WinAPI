#include<Windows.h> //мы не подключали winuser.h, потому что он подтягивается через Windows.h
#include"resource.h"

CHAR sz_login_invitation[] = "Input login";
CHAR sz_password_invitation[] = "Input password";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//WINAPI - конвенция вызова функции (_stdcall)
//в WinAPI все типы данных пишутся в заглавном регистре (так принято, можно использовать и обычный инт)
//hInstance - это экземпляр приложения (грубо говоря, запущенный экзешник, т.е. когда нам нужно обратиться к exe файлу, мы обращаемся к нему через hInstance) 
//hPrevInst - это параметр оставлен для обратной совместимости с windows98 (чтобы не изменять в корне всё api)
//lpCmdLine - это командная строка приложения (через нее в приложение могут передаваться параметры)
//nCmdShow - режим отображения окна (развернуто на весь экран, свернуто и т.д.)
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow) //аналог функции main в нашем консольном приложении
{
	//90% WinApi функций принимают 4 параметра.
	/*
	MessageBox(NULL, "Hellow World", "Info", MB_YESNOCANCEL | MB_ICONERROR | MB_HELP
	| MB_DEFBUTTON4 | MB_SYSTEMMODAL); //MB - Message Box. Эта функция возвращает код нажатой кнопки.
	*/
	//1й параметр - родительское окно. Родительское окно у нас отсутствувет, потому пишем NULL
	//2й параметр - текст сообщения
	//3й параметр - заголовок окна
	//4й параметр - набор кнопок окна сообщения, значок окна сообщения (через значок | задается значок)
	//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	//Модальным называется окно, которое блокирует родительское окно
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: //Определяем все то, что происходит при запуске
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_PASSWORD), WM_SETTEXT, 0, (LPARAM)sz_password_invitation);
	}
		break;
	case WM_COMMAND: //Определяем все то, что будет происходить при определенной команде, нажатии на кнопку, например.
	{
		switch (LOWORD(wParam))
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN); //Получаем ID окна текстового поля по имени ресурса
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		case IDC_EDIT_LOGIN:
		{
			//При выполнении различных действий над каким-либо элементом интерфейса(окном) этот элемент интерфейса, то бишь окно, получает уведомление(notification)
			//Уведомление(notification) - это самые обычные сообщения. Например, когда мы становимся в текстовое поле, то это текстовое поле получает уведомление EN_SETFOCUS
			//Когда мы "уходим" из текстового поля, то оно получает уведомление EN_KILLFOCUS
			//Фокус - это часть окна, которая принимает команды с клавиатуры
			//EN - Edit Notification
			/*CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};*/
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
				if(strcmp(sz_buffer, sz_login_invitation) == 0)
				SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)"");
				break;
			case EN_KILLFOCUS:
				if(strlen(sz_buffer) == 0)
					SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
				break;
			}
		}break;
		case IDC_BUTTON_COPY:
		{
			//CONST INT SIZE = 256; //размер буффера
			//CHAR sz_buffer[SIZE] = {}; //sz - stain(?) zero | си-строка
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN); //Получаем ID окна текстового поля по имени ресурса
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); //Копируем текст из текстового поля Password в sz_buffer
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDC_BUTTON_SET_TITLE:
		{
			CONST INT SIZE = 256; 
			CHAR sz_buffer[SIZE] = {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			//Изменение названия окна Visual Studio
			//SendMessage(FindWindow(NULL, "WinAPI - Microsoft Visual Studio"), WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK:
			MessageBox(NULL, "You pressed ok button", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}