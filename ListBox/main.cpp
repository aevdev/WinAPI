//ListBox
#define _CRT_SECURE_NO_WARNINGS //для sprintf()
#include<Windows.h> 
#include<cstdio> //для sprintf()
#include"resource.h"

CONST CHAR* string[] =
{
	//Вот эти строки мы добавил в ListBox
	"This", "is", "my", "first", "List","Box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//type name(parameters); - не полное объявление функции
//type calling_convention name(parameters); - чуть более полное (но все еще не полное) объявление функции
// type - тип возвращаемого значения
// calling_convention  - конвенция вызовов (соглашение о вызове функции):
// __syscall
// __stdcall	- WinAPI
// __fastcall	- x64
// __cdecl		- C/C++ 
// https://docs.microsoft.com/ru-ru/cpp/cpp/cdecl?view=msvc-170
// https://docs.microsoft.com/en-us/cpp/cpp/cdecl?view=msvc-170
// https://docs.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=msvc-170
// Конвенция вызовов определяет порядок вызова функции:
//  - кто очищает стек, вызывающая функция (caller) или  вызываемая функция (callee)
//  - как читается список передаваемых параметров - слева направо или справа налево
//	- или же параметры передаются через регистры (__fastcall) (самая быстрая память - это кэш память процессора первого уровня)
//	стек - это область память в оперативке, потому __fastcall, работающий непосредственно с кэш-памятью процессора отработает быстрее
//	однако, __fastcall лучше всего работает с небольшим количеством параметров (первые 4 параметра всегда передаются через регистры процессора)
// библиотека cstdarg помогает управлять количеством передаваемых параметров в функцию. можно почитать на досуге
// type - тип возвращаемого значения
 
//------------------------------------------------------------------------------------------------------------------------------------------- 
 
//HINSTANCE hInstance - экземпляр исполняемого файла (*.exe). Это загруженый в память *.exe-файл нашей программы.
//HINSTANCE hPrevInst - предыдущий экземпляр *.exe-файла. Этот параметр использовался в Windows 98 и оставлен для обратной совместимости.
//LPSTR lpCmdLine - это командная строка, с которой была запщуена программа LPSTR: LP - LongPointer STR - String ->
// -> LPSTR - LongPointer to String (указатель на строку - char*)
//INT cCmdShow - режим отображения окна: свернуто в окно, развернуто на весь экран, свернуто на панель задач и т.д. 
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow) //аналог функции main в нашем консольном приложении
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);
	//DialogBoxParam - это функция, которая запускает диалоговое окно.
	//MAKEINTRESOURCE - конвертирует номер ресурса в имя ресурса (в string)
	return 0;
}

//HWND - Handler to window. ОБРАБОТЧИК ОКНА, идентификатор окна, держатель окна.
//HWND - это идентификатор окна, через который к нему можно обратиться.
//HWND - это как имя переменной.
//UINT uMsg - Message (сообщение) UINT - unsigned int.
//wParam, lParam - это параметры сообщения, они зависят от того, какое именно uMsg мы посылаем окну.
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: //Это сообщение отправляется в окно при его создании.
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		//GetDlgItem(hwnd, IDC_LIST1); возвращает HWND элемента окна по ID ресурса нужного элемента
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); ++i)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
			//LB_ADDSTRING - добавляет указанную строку в ListBox
		}
		break;
	}
	case WM_COMMAND: //Это сообщение обрабатывает нажатие на кнопки и другие элементы интерфейса окна.
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {}; //В эту строку мы скопируем выделенную строку ListBox'а.
			//А эту строку мы будем отображать в MessageBox:
			CHAR sz_message[SIZE] = {};

			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			int index = SendMessage(hListBox, LB_GETCURSEL, 0, 0); //Получаем числовой индекс выделенного элемента ListBox
			SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, "You have chosen № %d with the value of \"%s\".", index, sz_buffer);
			//Функция sprintf() выполняет форматирование строк
			//sz_message - Это буфер, в который сохранится отформатированная строка.
			//"Вы выбрали..." - это шаблон строки, т.е. то, как она должна выглядеть
			//%d - вставить в шаблонную строку десятичное целое число (decimal)
			//%s - вставить в шаблонную строку подстроку.
			//Все вставляемые значения перечислены далее в передаваемых параметрах: index, sz_buffer....
			//количество параметров функции sprintf() неограниченно
			//функция sprintf() позволят вставлять в строку какие угодно значения
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);	// | побитовое ИЛИ
		}
			break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0); break;

	}
	return FALSE;
}