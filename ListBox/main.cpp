//ListBox
#define _CRT_SECURE_NO_WARNINGS //��� sprintf()
#include<Windows.h> 
#include<cstdio> //��� sprintf()
#include"resource.h"

CONST CHAR* string[] =
{
	//��� ��� ������ �� ������� � ListBox
	"This", "is", "my", "first", "List","Box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//type name(parameters); - �� ������ ���������� �������
//type calling_convention name(parameters); - ���� ����� ������ (�� ��� ��� �� ������) ���������� �������
// type - ��� ������������� ��������
// calling_convention  - ��������� ������� (���������� � ������ �������):
// __syscall
// __stdcall	- WinAPI
// __fastcall	- x64
// __cdecl		- C/C++ 
// https://docs.microsoft.com/ru-ru/cpp/cpp/cdecl?view=msvc-170
// https://docs.microsoft.com/en-us/cpp/cpp/cdecl?view=msvc-170
// https://docs.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=msvc-170
// ��������� ������� ���������� ������� ������ �������:
//  - ��� ������� ����, ���������� ������� (caller) ���  ���������� ������� (callee)
//  - ��� �������� ������ ������������ ���������� - ����� ������� ��� ������ ������
//	- ��� �� ��������� ���������� ����� �������� (__fastcall) (����� ������� ������ - ��� ��� ������ ���������� ������� ������)
//	���� - ��� ������� ������ � ����������, ������ __fastcall, ���������� ��������������� � ���-������� ���������� ���������� �������
//	������, __fastcall ����� ����� �������� � ��������� ����������� ���������� (������ 4 ��������� ������ ���������� ����� �������� ����������)
// ���������� cstdarg �������� ��������� ����������� ������������ ���������� � �������. ����� �������� �� ������
// type - ��� ������������� ��������
 
//------------------------------------------------------------------------------------------------------------------------------------------- 
 
//HINSTANCE hInstance - ��������� ������������ ����� (*.exe). ��� ���������� � ������ *.exe-���� ����� ���������.
//HINSTANCE hPrevInst - ���������� ��������� *.exe-�����. ���� �������� ������������� � Windows 98 � �������� ��� �������� �������������.
//LPSTR lpCmdLine - ��� ��������� ������, � ������� ���� �������� ��������� LPSTR: LP - LongPointer STR - String ->
// -> LPSTR - LongPointer to String (��������� �� ������ - char*)
//INT cCmdShow - ����� ����������� ����: �������� � ����, ���������� �� ���� �����, �������� �� ������ ����� � �.�. 
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow) //������ ������� main � ����� ���������� ����������
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);
	//DialogBoxParam - ��� �������, ������� ��������� ���������� ����.
	//MAKEINTRESOURCE - ������������ ����� ������� � ��� ������� (� string)
	return 0;
}

//HWND - Handler to window. ���������� ����, ������������� ����, ��������� ����.
//HWND - ��� ������������� ����, ����� ������� � ���� ����� ����������.
//HWND - ��� ��� ��� ����������.
//UINT uMsg - Message (���������) UINT - unsigned int.
//wParam, lParam - ��� ��������� ���������, ��� ������� �� ����, ����� ������ uMsg �� �������� ����.
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: //��� ��������� ������������ � ���� ��� ��� ��������.
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		//GetDlgItem(hwnd, IDC_LIST1); ���������� HWND �������� ���� �� ID ������� ������� ��������
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); ++i)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
			//LB_ADDSTRING - ��������� ��������� ������ � ListBox
		}
		break;
	}
	case WM_COMMAND: //��� ��������� ������������ ������� �� ������ � ������ �������� ���������� ����.
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {}; //� ��� ������ �� ��������� ���������� ������ ListBox'�.
			//� ��� ������ �� ����� ���������� � MessageBox:
			CHAR sz_message[SIZE] = {};

			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			int index = SendMessage(hListBox, LB_GETCURSEL, 0, 0); //�������� �������� ������ ����������� �������� ListBox
			SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, "You have chosen � %d with the value of \"%s\".", index, sz_buffer);
			//������� sprintf() ��������� �������������� �����
			//sz_message - ��� �����, � ������� ���������� ����������������� ������.
			//"�� �������..." - ��� ������ ������, �.�. ��, ��� ��� ������ ���������
			//%d - �������� � ��������� ������ ���������� ����� ����� (decimal)
			//%s - �������� � ��������� ������ ���������.
			//��� ����������� �������� ����������� ����� � ������������ ����������: index, sz_buffer....
			//���������� ���������� ������� sprintf() �������������
			//������� sprintf() �������� ��������� � ������ ����� ������ ��������
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);	// | ��������� ���
		}
			break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0); break;

	}
	return FALSE;
}