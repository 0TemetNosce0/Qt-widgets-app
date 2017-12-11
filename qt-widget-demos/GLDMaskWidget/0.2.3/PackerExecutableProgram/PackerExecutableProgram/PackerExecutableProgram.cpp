// PackerExecutableProgram.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include <vector>
#include <iostream>

#include <stdio.h>
#include <windows.h>

using namespace std;

const LPCWSTR maskExePath = _T("bin\\GLDMaskWidget.exe");
const LPCWSTR userExePath = _T("bin\\QLightBoxWidget.exe");

LPCWSTR getExePath(LPCWSTR exePath)
{
    TCHAR filePath[MAX_PATH];
    memset(filePath, 0, MAX_PATH);
    GetModuleFileName(NULL, filePath, MAX_PATH);
    (_tcsrchr(filePath, _T('\\')))[1] = 0;
    lstrcat(filePath, exePath);
    return filePath;
}

void executeUserExe(LPCWSTR exePath)
{
    TCHAR filePath[MAX_PATH];
    memset(filePath, 0, MAX_PATH);
    GetModuleFileName(NULL, filePath, MAX_PATH);
    (_tcsrchr(filePath, _T('\\')))[1] = 0;
    lstrcat(filePath, exePath);

    //LPCWSTR filePath = getExePath(exePath);

    SHELLEXECUTEINFO ShellInfo;

    memset(&ShellInfo, 0, sizeof(ShellInfo));
    ShellInfo.cbSize = sizeof(ShellInfo);
    ShellInfo.hwnd = NULL;
    ShellInfo.lpVerb = _T("open");
    ShellInfo.lpFile = filePath;
    ShellInfo.nShow = SW_SHOWNORMAL;
    ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;

    ShellExecuteEx(&ShellInfo);
}

size_t executeProcess(LPCWSTR fullPathToExe)
{
    size_t iReturnVal = 0, iPos = 0;
    DWORD dwExitCode = 0;

    /* CreateProcess API initialization */
    STARTUPINFOW siStartupInfo;
    PROCESS_INFORMATION piProcessInfo;
    memset(&siStartupInfo, 0, sizeof(siStartupInfo));
    memset(&piProcessInfo, 0, sizeof(piProcessInfo));
    siStartupInfo.cb = sizeof(siStartupInfo);

    if (CreateProcessW(fullPathToExe,
        nullptr, 0, 0, false,
        CREATE_DEFAULT_ERROR_MODE, 0, 0,
        &siStartupInfo, &piProcessInfo) != false)
    {
        /* Watch the process. */
        dwExitCode = WaitForSingleObject(piProcessInfo.hProcess, INFINITE);

        if (dwExitCode == WAIT_OBJECT_0)
        {
            executeUserExe(userExePath);
        }
    }
    else
    {
        /* CreateProcess failed */
        iReturnVal = GetLastError();
    }

    /* Release handles */
    CloseHandle(piProcessInfo.hProcess);
    CloseHandle(piProcessInfo.hThread);

    return iReturnVal;
}

void executeMaskExe(LPCWSTR exePath)
{
    TCHAR filePath[MAX_PATH];
    memset(filePath, 0, MAX_PATH);
    GetModuleFileName(NULL, filePath, MAX_PATH);
    (_tcsrchr(filePath, _T('\\')))[1] = 0;
    lstrcat(filePath, exePath);

    executeProcess(filePath);
}

int main(int argc, _TCHAR* argv[])
{
    // Stealth(); // 调用此函数,控制台窗口会有短暂的闪烁
    FreeConsole();

    executeMaskExe(maskExePath);

    return FALSE;
}

