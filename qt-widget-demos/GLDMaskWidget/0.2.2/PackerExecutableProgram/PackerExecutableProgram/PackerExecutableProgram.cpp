// PackerExecutableProgram.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include <vector>
#include <iostream>

#include <stdio.h>
#include <windows.h>

using namespace std;

char* tchar2char(TCHAR* tchStr)
{
    size_t iLen = 2 * wcslen(tchStr);
    char* chRtn = new char[iLen + 1];
    wcstombs(chRtn, tchStr, iLen + 1);
    return chRtn;
}

TCHAR *char2tchar(char *str)
{
    size_t iLen = strlen(str);
    TCHAR *chRtn = new TCHAR[iLen + 1];
    mbstowcs(chRtn, str, iLen + 1);
    return chRtn;
}

void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}

size_t executeProcess(std::wstring fullPathToExe, std::wstring parameters, size_t secondsToWait)
{
    size_t iReturnVal = 0, iPos = 0;
    DWORD dwExitCode = 0;
    std::wstring sTempStr = L"";

    /* - NOTE - You should check here to see if the exe even exists */
    /* Add a space to the beginning of the Parameters */
    if (parameters.size() != 0)
    {
        if (parameters[0] != L' ')
        {
            parameters.insert(0, L" ");
        }
    }

    /* The first parameter needs to be the exe itself */
    sTempStr = fullPathToExe;
    iPos = sTempStr.find_last_of(L"\\");
    sTempStr.erase(0, iPos + 1);
    parameters = sTempStr.append(parameters);

    /* CreateProcessW can modify Parameters thus we allocate needed memory */
    wchar_t * pwszParam = new wchar_t[parameters.size() + 1];

    if (pwszParam == 0)
    {
        return 1;
    }

    const wchar_t* pchrTemp = parameters.c_str();
    wcscpy_s(pwszParam, parameters.size() + 1, pchrTemp);

    /* CreateProcess API initialization */
    STARTUPINFOW siStartupInfo;
    PROCESS_INFORMATION piProcessInfo;
    memset(&siStartupInfo, 0, sizeof(siStartupInfo));
    memset(&piProcessInfo, 0, sizeof(piProcessInfo));
    siStartupInfo.cb = sizeof(siStartupInfo);

    if (CreateProcessW(const_cast<LPCWSTR>(fullPathToExe.c_str()),
        pwszParam, 0, 0, false,
        CREATE_DEFAULT_ERROR_MODE, 0, 0,
        &siStartupInfo, &piProcessInfo) != false)
    {
        /* Watch the process. */
        dwExitCode = WaitForSingleObject(piProcessInfo.hProcess, INFINITE);

        if (dwExitCode == WAIT_OBJECT_0)
        {
            TCHAR szFilePath[MAX_PATH];
            memset(szFilePath, 0, MAX_PATH);
            GetModuleFileName(NULL, szFilePath, MAX_PATH);
            (_tcsrchr(szFilePath, _T('\\')))[1] = 0;
            char* pExePath = tchar2char(szFilePath);
            strcat(pExePath, "\\bin\\QLightBoxWidget.exe");

            //::WinExec(pExePath, SW_SHOWNORMAL);
            
            SHELLEXECUTEINFO ShellInfo;

            memset(&ShellInfo, 0, sizeof(ShellInfo));
            ShellInfo.cbSize = sizeof(ShellInfo);
            ShellInfo.hwnd = NULL;
            ShellInfo.lpVerb = _T("open");
            ShellInfo.lpFile = char2tchar(pExePath);
            ShellInfo.nShow = SW_SHOWNORMAL;
            ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;

            ShellExecuteEx(&ShellInfo);
        }
    }
    else
    {
        /* CreateProcess failed */
        iReturnVal = GetLastError();
    }

    /* Free memory */
    delete[]pwszParam;
    pwszParam = 0;

    /* Release handles */
    CloseHandle(piProcessInfo.hProcess);
    CloseHandle(piProcessInfo.hThread);

    return iReturnVal;
}

int main(int argc, _TCHAR* argv[])
{
    // Stealth(); // 调用此函数,控制台窗口会有短暂的闪烁
    FreeConsole();

    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);
    (_tcsrchr(szPath, _T('\\')))[1] = 0;
    char* pExePath = tchar2char(szPath);
    strcat(pExePath, "bin\\GLDMaskWidget.exe");

    TCHAR * pTemp = char2tchar(pExePath);
    executeProcess(pTemp, _T(""), 1);

    return FALSE;
}

