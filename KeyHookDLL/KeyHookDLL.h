#pragma once



LRESULT CALLBACK hookProc(int code, WPARAM wParam, LPARAM lParam);

extern "C" _declspec(dllexport) bool installHook();

extern "C" _declspec(dllexport) bool unInstallHook();