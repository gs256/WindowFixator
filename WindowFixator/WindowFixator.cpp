#include <iostream>
#include <Windows.h>
#include "KeyHook/KeyHook.h"

bool AUTORUN = true;

void ToggleWindowPos();
void AddToAutorun();

int main() {
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

//void AddToAutorun() {
//	//HKEY hKey;
//	char szPath[255];
//	GetModuleFileNameA(NULL, szPath, sizeof(szPath));
//
//	char command[255];
//	strcpy_s(command, "REG ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Run /v WindowsFixator /d ");
//	strcat(command, szPath);
//
//	system("REG ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Run /v WindowsFixator /d " + (szPath));
//}

void AddToAutorun() {
	HKEY hKey;
	wchar_t szPath[4096];
	GetModuleFileNameW(NULL, szPath, sizeof(szPath));
	RegCreateKeyExA(HKEY_LOCAL_MACHINE,
		"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
		NULL,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_SET_VALUE,
		NULL,
		&hKey,
		NULL);

	if (hKey) {
		RegSetValueExW(hKey, L"My program", NULL, REG_SZ, (LPBYTE)szPath, wcslen(szPath));
		RegCloseKey(hKey);
	}

}