#include <iostream>
#include <Windows.h>
#include "KeyHook/KeyHook.h"

bool AUTORUN = true;

void ToggleWindowPos();
void AddToAutorun();

int main() {
	// Make window hidden
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (AUTORUN)
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
	char szPath[1024];
	GetModuleFileNameA(NULL, szPath, sizeof(szPath));
	RegCreateKeyExA(HKEY_LOCAL_MACHINE,
		"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
		NULL,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_SET_VALUE,
		NULL,
		&hKey,
		NULL);

	// Add a value to the "run" registry key
	if (hKey) {
		RegSetValueExA(hKey, "WindowFixator", NULL, REG_SZ, (LPBYTE)szPath, strlen(szPath));
		RegCloseKey(hKey);
	}
}