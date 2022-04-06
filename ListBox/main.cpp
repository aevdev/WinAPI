//ListBox
#include<Windows.h> 
#include"resource.h"

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
		break;
	case WM_COMMAND: //Это сообщение обрабатывает нажатие на кнопки и другие элементы интерфейса окна.
		switch (LOWORD(wParam))
		{
		case IDOK:
			break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0); break;
	}
	return FALSE;
}