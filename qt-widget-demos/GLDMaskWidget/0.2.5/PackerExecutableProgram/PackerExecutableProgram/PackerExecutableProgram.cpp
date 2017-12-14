// PackerExecutableProgram.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

using namespace std;

const LPCWSTR iniPath = _T("config\\NewGuide.ini");

// http://www.cnblogs.com/kex1n/archive/2011/04/10/2011254.html
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

LPCWSTR getPath(LPCWSTR exeName)
{
    TCHAR* filePath = new TCHAR[MAX_PATH];
    memset(filePath, 0, MAX_PATH);
    GetModuleFileName(NULL, filePath, MAX_PATH);
    (_tcsrchr(filePath, _T('\\')))[1] = 0;
    lstrcat(filePath, exeName);
    return filePath;
}

void executeUserExe(LPCWSTR userExeName)
{
    LPCWSTR filePath = getPath(userExeName);

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

size_t executeProcess(LPCWSTR fullPathToExe, LPCWSTR userExePath)
{
    size_t iReturnVal = 0;
    DWORD dwExitCode = 0;

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
        dwExitCode = WaitForSingleObject(piProcessInfo.hProcess, INFINITE);

        if (dwExitCode == WAIT_OBJECT_0)
        {
            executeUserExe(userExePath);
        }
    }
    else
    {
        iReturnVal = GetLastError();
    }

    CloseHandle(piProcessInfo.hProcess);
    CloseHandle(piProcessInfo.hThread);

    return iReturnVal;
}

void executeMaskAndUserExe(LPCWSTR maskExeName, LPCWSTR userExeName)
{
    LPCWSTR maskFilePath = getPath(maskExeName);

    executeProcess(maskFilePath, userExeName);
}

int main(int argc, _TCHAR* argv[])
{
    // 隐藏控制台窗口
    FreeConsole();

    // ini文件路径
    LPCWSTR filePath = getPath(iniPath);

    // 蒙版EXE名字
    LPTSTR maskWidgetName = new TCHAR[MAX_PATH];
    ::GetPrivateProfileString(_T("Mask"), _T("MaskWidgetName"), _T(""), maskWidgetName, MAX_PATH, filePath); 
    lstrcat(maskWidgetName, _T(".exe"));

    // 用户EXE名字
    LPTSTR userExecutable = new TCHAR[MAX_PATH];
    ::GetPrivateProfileString(_T("User"), _T("UserExecutable"), _T(""), userExecutable, MAX_PATH, filePath); 
    lstrcat(userExecutable, _T(".exe"));

    // 标志位,用于表示是否启动蒙版;若为1,则直接启动用户程序,否则,先启动蒙版程序,再启动用户程序
    int mask = ::GetPrivateProfileInt(_T("General"), _T("GLDMaskWidget"), 0, filePath);

    if (1 == mask)
    {
        executeUserExe(userExecutable);
    }
    else
    {
        executeMaskAndUserExe(maskWidgetName, userExecutable);
    }

    return FALSE;
}

