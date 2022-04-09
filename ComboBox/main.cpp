#include <Windows.h>
#include <cstdio>
#include "resource.h"

CONST CHAR* string[] =
{
	"This", "is", "my", "first", "Combo","Box", "FirstString", "SecondString"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); ++i)
		{
			SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)string[i]); //Как я понял, LB - ListBox, в CB - ComboBox, так что если ничего не добавится, в первую очередь заменить LB на CB
		}
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			CHAR sz_message[SIZE] = {};

			HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
			int index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0); //Здесь тоже LB -> CB
			SendMessage(hComboBox, CB_GETLBTEXT, index, (LPARAM)sz_buffer); //Здесь тоже LB -> CB
			sprintf_s(sz_message, "You have chosen №%d with the value of \"%s\"", index, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0); break;
	}

	return FALSE;
}