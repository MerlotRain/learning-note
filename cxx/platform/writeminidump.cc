#pragma once
#include <windows.h>
#include <DbgHelp.h>
#include <winnt.h>
#include <time.h>
#include <locale>
#include <codecvt>
#include <tchar.h>
#pragma comment( lib, "Dbghelp.lib" )
#include "crashreturnfunction.h"
#include <QDebug>
#include"errhandlingapi.h"


LONG __stdcall ApplicationCrashHandler(EXCEPTION_POINTERS* pException)
{
    qDebug() << "Crash_Time" << QDateTime::currentDateTime().toString();

    spdlog::drop_all();

    QDateTime CurDTime = QDateTime::currentDateTime();

    QString dumpFilePath = CS::Core::ICore::getDefaultPath()+ "/dump/" + CurDTime.toString("yyyy_MM_dd_hh_mm_ss") + ".dmp";
    std::wstring wide = dumpFilePath.toStdWString();
    EXCEPTION_RECORD *record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode));
    QString errAddr(QString::number((uint)record->ExceptionAddress));
    QString errFlag(QString::number(record->ExceptionFlags));
    QString errPara(QString::number(record->NumberParameters));
    HANDLE DumpHandle = CreateFileW(wide.c_str(),GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (DumpHandle != INVALID_HANDLE_VALUE) {
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;
        MINIDUMP_TYPE mDumpValue = static_cast<MINIDUMP_TYPE>(
                MiniDumpNormal 
            );

        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), DumpHandle, mDumpValue, &dumpInfo, NULL, NULL);
        CloseHandle(DumpHandle);
    }
    qDebug() << "EXCEPTION_EXECUTE_HANDLER:" << EXCEPTION_EXECUTE_HANDLER;

    CS::Widgets::FramelessMessageBox::warning(nullptr, "Error", "Sorry , Crash,Please contact the developer.");
    crashreturnfunction postObject;
    QProcess process;
    QStringList param;
    QString exePath = postObject.getCrashExePath();
    param = postObject.getCrashExePram();
    qDebug() << "param" << param.size();
    for (int i = 0; i < param.size(); i++)
    {
        qDebug() << "param:" << i << param.at(i);
    }
    process.startDetached(exePath, param);

    return EXCEPTION_EXECUTE_HANDLER;
}
static BOOL PreventFuncall(void *oldfun, void *newfun)
{
    void* pOrgEntry = oldfun;
    if (pOrgEntry == NULL)
        return FALSE;
    DWORD dwOldProtect = 0;
    SIZE_T jmpSize = 5;
#ifdef _M_X64
    jmpSize = 13;
#endif
    BOOL bProt = VirtualProtect(pOrgEntry, jmpSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    BYTE newJump[20];
    void* pNewFunc = newfun;
#ifdef _M_IX86
    DWORD dwOrgEntryAddr = (DWORD)pOrgEntry;
    dwOrgEntryAddr += jmpSize;
    DWORD dwNewEntryAddr = (DWORD)pNewFunc;
    DWORD dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;
    newJump[0] = 0xE9;
    memcpy(&newJump[1], &dwRelativeAddr, sizeof(pNewFunc));
#elif _M_X64
    newJump[0] = 0x49;
    newJump[1] = 0xBB;
    memcpy(&newJump[2], &pNewFunc, sizeof(pNewFunc));
    newJump[10] = 0x41;
    newJump[11] = 0xFF;
    newJump[12] = 0xE3;
#endif
    SIZE_T bytesWritten;
    BOOL bRet = WriteProcessMemory(GetCurrentProcess(), pOrgEntry, newJump, jmpSize, &bytesWritten);
    if (bProt != FALSE) {
        DWORD dwBuf;
        VirtualProtect(pOrgEntry, jmpSize, dwOldProtect, &dwBuf);
    }
    return bRet;
}
void DisableSetUnhandledExceptionFilter()
{
    HMODULE h_hand = LoadLibrary(TEXT("kernel32.dll"));
    void* addr = (void*)GetProcAddress(h_hand, "SetUnhandledExceptionFilter");
    void *newfun = nullptr;
    if (addr)
    {
        unsigned char code[16];
        int size = 0;
        code[size++] = 0x33;
        code[size++] = 0xC0;
        code[size++] = 0xC2;
        code[size++] = 0x00;
        code[size++] = 0x00;
        DWORD dwOldFlag, dwTempFlag;

        VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
        qDebug("WriteProcessMemory start!");
        WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
        qDebug("WriteProcessMemory end!");
        VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
    }
}
void RunCrashHandlerLocal()
{
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
	DisableSetUnhandledExceptionFilter();
	QString paths = CS::Core::ICore::getDefaultPath() + "/dump";
	QDir dir(paths);
	if (!dir.exists())
	{
		dir.mkdir(paths);
	}
}