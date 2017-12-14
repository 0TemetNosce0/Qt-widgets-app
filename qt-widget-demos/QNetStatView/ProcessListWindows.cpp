#include "ProcessListWindows.h"


#if defined(Q_OS_WIN)
typedef LONG (WINAPI *PROCNTQSIP)(HANDLE,UINT,PVOID,ULONG,PULONG);

PROCNTQSIP NtQueryInformationProcess;
#endif


#if defined(Q_OS_WIN)
BOOL ProcessListWindows::GetProcessCmdLine(DWORD dwId, LPWSTR wBuf, DWORD dwBufLen)
{
    LONG                      status;
    HANDLE                    hProcess;
    PROCESS_BASIC_INFORMATION pbi;
    PEB                       Peb;
    PROCESS_PARAMETERS        ProcParam;
    DWORD                     dwDummy;
    DWORD                     dwSize;
    LPVOID                    lpAddress;
    BOOL                      bRet = FALSE;

    // Get process handle
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, dwId);

    if (!hProcess)
    {
        return FALSE;
    }

    // Retrieve information
    status = NtQueryInformationProcess(hProcess, ProcessBasicInformation, (PVOID)&pbi, sizeof(PROCESS_BASIC_INFORMATION), NULL);


    if (status)
       goto cleanup;

    if ( !ReadProcessMemory(hProcess, pbi.PebBaseAddress, &Peb, sizeof(PEB), &dwDummy) )
       goto cleanup;

    if ( !ReadProcessMemory(hProcess, Peb.ProcessParameters, &ProcParam, sizeof(PROCESS_PARAMETERS), &dwDummy) )
       goto cleanup;

    lpAddress = ProcParam.CommandLine.Buffer;
    dwSize = ProcParam.CommandLine.Length;

    if (dwBufLen<dwSize)
       goto cleanup;

    if ( !ReadProcessMemory(hProcess, lpAddress, wBuf, dwSize, &dwDummy) )
       goto cleanup;

    bRet = TRUE;

cleanup:
    CloseHandle (hProcess);

    return bRet;
}

#endif

ProcessListWindows::ProcessListWindows(QObject *parent) : QObject(parent)
{

}

int ProcessListWindows::initProccessList()
{
    return 1;
}

QString  ProcessListWindows::getProgram(QString pid)
{

    int iPID = pid.toInt();

#if defined(Q_OS_WIN)
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, iPID);
    WCHAR szFilePath[MAX_PATH] = {0};
    GetModuleFileNameEx(hProcess, NULL, szFilePath, MAX_PATH);
    CloseHandle(hProcess);
    return QString::fromWCharArray(szFilePath);

#endif

    return "";

}


QString  ProcessListWindows::getCmdline(QString pid)
{
    #if defined(Q_OS_WIN)
        NtQueryInformationProcess = (PROCNTQSIP)GetProcAddress( GetModuleHandle((const WCHAR*)"NTDLL"), "NtQueryInformationProcess" );

        if (!NtQueryInformationProcess) return "";

        DWORD dwId;
        sscanf(pid.toStdString().c_str(),"%lu",&dwId);

        WCHAR wstr[255];

        if (GetProcessCmdLine(dwId,wstr,sizeof(wstr)))
        {
           //wprintf(L"Command line for process %lu is:\n%s\n",dwId,wstr);
           return QString::fromWCharArray(wstr);
        }
           //wprintf(L"Could not get command line!");
    #endif

    return "";
}

QStringList ProcessListWindows::getSockets(QString pid)
{
    return QStringList();
}

sProccess ProcessListWindows::getProc(QString pid)
{
    sProccess proc;
    proc.pid = pid;
    //proc.sockets=getSockets(pid);
    proc.program = getProgram(pid);
    proc.cmdline = getCmdline(pid);

    return proc;
}
