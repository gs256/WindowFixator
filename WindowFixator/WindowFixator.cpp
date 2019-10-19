#include <iostream>
#include <Windows.h>
#include "KeyHook/KeyHook.h"

void f() 
{
	//printf("%s", "Action\n");
	HWND hwnd = GetForegroundWindow();

	if (::GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST)
		SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	else
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  	
}


int main()
{	
	StartKeyHook(f);
	system("PAUSE");
}

