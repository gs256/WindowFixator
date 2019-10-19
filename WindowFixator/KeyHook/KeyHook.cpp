#include <Windows.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include "KeyHook.h"
#include <iostream>

using namespace std;

void (*userFunc)();
bool pressedKeys[255] = {};
unsigned char userKeys[2] = {0x20, 0x8};
unsigned char numOfPressed = 0;

LRESULT CALLBACK CheckShortcut(int iCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT pHook = (PKBDLLHOOKSTRUCT)lParam;
	bool keyState = NULL;
	unsigned char keyCode = pHook->vkCode;

	for (unsigned char key : userKeys)
	{
		if (keyCode == key)
		{
			if (wParam == WM_KEYDOWN)
				numOfPressed++;
			else if (wParam == WM_KEYUP)
				numOfPressed--;
		}
	}

	if (numOfPressed == size(userKeys))
		userFunc();

	return CallNextHookEx(NULL, iCode, wParam, lParam);
}

void StartKeyHook(void (*shortcutFunc)())
{
	userFunc = shortcutFunc;
	HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, CheckShortcut, NULL, NULL);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hHook);
}





