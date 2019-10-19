#pragma once

LRESULT CALLBACK CheckShortcut(int iCode, WPARAM wParam, LPARAM lParam);
void StartKeyHook(void(*shortcutFunc)());