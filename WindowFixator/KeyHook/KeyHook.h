#pragma once

// Checks whether the shortcut is pressed
LRESULT CALLBACK CheckShortcut(int iCode, WPARAM wParam, LPARAM lParam);

// Starts the app
void StartKeyHook(void(*shortcutFunc)());