#ifndef PROCESSLISTWINDOWS_H
#define PROCESSLISTWINDOWS_H

#include <QObject>

#include <QString>
#include <QStringList>
#include <QMap>
#include "Process.h"

#if defined(Q_OS_WIN)
#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include <tchar.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>


#define ProcessBasicInformation 0

typedef struct
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct
{
    ULONG          AllocationSize;
    ULONG          ActualSize;
    ULONG          Flags;
    ULONG          Unknown1;
    UNICODE_STRING Unknown2;
    HANDLE         InputHandle;
    HANDLE         OutputHandle;
    HANDLE         ErrorHandle;
    UNICODE_STRING CurrentDirectory;
    HANDLE         CurrentDirectoryHandle;
    UNICODE_STRING SearchPaths;
    UNICODE_STRING ApplicationName;
    UNICODE_STRING CommandLine;
    PVOID          EnvironmentBlock;
    ULONG          Unknown[9];
    UNICODE_STRING Unknown3;
    UNICODE_STRING Unknown4;
    UNICODE_STRING Unknown5;
    UNICODE_STRING Unknown6;
} PROCESS_PARAMETERS, *PPROCESS_PARAMETERS;

typedef struct
{
    ULONG               AllocationSize;
    ULONG               Unknown1;
    HINSTANCE           ProcessHinstance;
    PVOID               ListDlls;
    PPROCESS_PARAMETERS ProcessParameters;
    ULONG               Unknown2;
    HANDLE              Heap;
} PEB, *PPEB;

typedef struct
{
    DWORD ExitStatus;
    PPEB  PebBaseAddress;
    DWORD AffinityMask;
    DWORD BasePriority;
    ULONG UniqueProcessId;
    ULONG InheritedFromUniqueProcessId;
}   PROCESS_BASIC_INFORMATION;

#endif

class ProcessListWindows : public QObject{
    Q_OBJECT
    public:
        explicit ProcessListWindows(QObject *parent = 0);
        int initProccessList();
        sProccess getProc(QString pid);

    private:
        QStringList getSockets(QString pid);
        QString getProgram(QString pid);
        QString getCmdline(QString pid);

        #if defined(Q_OS_WIN)
        BOOL GetProcessCmdLine(DWORD dwId,LPWSTR wBuf,DWORD dwBufLen);
        #endif



    signals:

    public slots:

};

#endif // PROCESSLISTWINDOWS_H
