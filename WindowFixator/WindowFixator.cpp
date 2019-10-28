#include <iostream>
#include <Windows.h>
#include "KeyHook/KeyHook.h"

void ToggleWindowPos();
void AddToAutorun();

int main() {	
	AddToAutorun();
	StartKeyHook(ToggleWindowPos);
}

void ToggleWindowPos() {
	HWND hwnd = GetForegroundWindow();

	// Whether the window is already topmost
	if (::GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST)
		// Make notopmost
		SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	else
		// Make topmost
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void AddToAutorun() {
	HKEY hKey;
	wchar_t szPath[255];
	GetModuleFileName(NULL, szPath, sizeof(szPath));
	LSTATUS lres = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);

	if (hKey){
		RegSetValueEx(hKey, L"WinFix", NULL, REG_SZ, (LPBYTE)szPath, lstrlenW(szPath));
		RegCloseKey(hKey);
	}
}