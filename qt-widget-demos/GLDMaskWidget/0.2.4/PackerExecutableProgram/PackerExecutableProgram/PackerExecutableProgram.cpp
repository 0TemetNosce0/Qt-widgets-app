// PackerExecutableProgram.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include <windows.h>

using namespace std;

const LPCWSTR iniPath = _T("config\\NewGuide.ini");
//TCHAR filePath[MAX_PATH];

LPCWSTR getPath(LPCWSTR exePath)
{
    //TCHAR filePath[MAX_PATH];
    TCHAR* filePath = new TCHAR[MAX_PATH];
    memset(filePath, 0, MAX_PATH);
    GetModuleFileName(NULL, filePath, MAX_PATH);
    (_tcsrchr(filePath, _T('\\')))[1] = 0;
    lstrcat(filePath, exePath);
    return filePath;
}

void executeUserExe(LPCWSTR exePath)
{
    //TCHAR filePath[MAX_PATH];
    //memset(filePath, 0, MAX_PATH);
    //GetModuleFileName(NULL, filePath, MAX_PATH);
    //(_tcsrchr(filePath, _T('\\')))[1] = 0;
    //lstrcat(filePath, exePath);

    LPCWSTR filePath = getPath(exePath);

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

void executeMaskAndUserExe(LPCWSTR maskPath, LPCWSTR userPath)
{
    //TCHAR filePath[MAX_PATH];
    //memset(filePath, 0, MAX_PATH);
    //GetModuleFileName(NULL, filePath, MAX_PATH);
    //(_tcsrchr(filePath, _T('\\')))[1] = 0;
    //lstrcat(filePath, maskPath);
    LPCWSTR maskFilePath = getPath(maskPath);

    executeProcess(maskFilePath, userPath);
}

int main(int argc, _TCHAR* argv[])
{
    // ���ؿ���̨����
    FreeConsole();

    // ini�ļ�·��
    //TCHAR filePath[MAX_PATH];
    //memset(filePath, 0, MAX_PATH);
    //GetModuleFileName(NULL, filePath, MAX_PATH);
    //(_tcsrchr(filePath, _T('\\')))[1] = 0;
    //lstrcat(filePath, iniPath);
    LPCWSTR filePath = getPath(iniPath);

    // �ɰ�EXE·��
    LPTSTR maskWidgetName = new TCHAR[MAX_PATH];
    ::GetPrivateProfileString(_T("Mask"), _T("MaskWidgetName"), _T(""), maskWidgetName, MAX_PATH, filePath); 
    lstrcat(maskWidgetName, _T(".exe"));

    // �û�EXE·��
    LPTSTR userExecutable = new TCHAR[MAX_PATH];
    ::GetPrivateProfileString(_T("User"), _T("UserExecutable"), _T(""), userExecutable, MAX_PATH, filePath); 
    lstrcat(userExecutable, _T(".exe"));

    // ��־λ,���ڱ�ʾ�Ƿ������ɰ�,��Ϊ1,��ֱ�������û�����,����,�������ɰ����,�������û�����
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

