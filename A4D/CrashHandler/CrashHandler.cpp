#include "../Engine/stdafx.h"
// 添加对dbghelp.lib的编译依赖
#pragma comment(lib, "dbghelp.lib")
using namespace std;
const int MAX_ADDRESS_LENGTH = 32;
const int MAX_NAME_LENGTH = 1024;

// CallStack信息
struct CallStackInfo
{
	CHAR ModuleName[MAX_NAME_LENGTH];
	CHAR MethodName[MAX_NAME_LENGTH];
	CHAR FileName[MAX_NAME_LENGTH];
	CHAR LineNumber[MAX_NAME_LENGTH];
};

// 得到CallStack信息
vector<CallStackInfo> GetCallStack(const CONTEXT *pContext)
{
	HANDLE hProcess = GetCurrentProcess();
	SymInitialize(hProcess, NULL, TRUE);
	CONTEXT c = *pContext;
	STACKFRAME64 sf;
	memset(&sf, 0, sizeof(STACKFRAME64));
	DWORD dwImageType = IMAGE_FILE_MACHINE_I386;
	// 不同的CPU类型，具体信息可查询MSDN
#ifdef _M_IX86
	sf.AddrPC.Offset = c.Eip;
	sf.AddrPC.Mode = AddrModeFlat;
	sf.AddrStack.Offset = c.Esp;
	sf.AddrStack.Mode = AddrModeFlat;
	sf.AddrFrame.Offset = c.Ebp;
	sf.AddrFrame.Mode = AddrModeFlat;
#elif _M_X64
	dwImageType = IMAGE_FILE_MACHINE_AMD64;
	sf.AddrPC.Offset = c.Rip;
	sf.AddrPC.Mode = AddrModeFlat;
	sf.AddrFrame.Offset = c.Rsp;
	sf.AddrFrame.Mode = AddrModeFlat;
	sf.AddrStack.Offset = c.Rsp;
	sf.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
	dwImageType = IMAGE_FILE_MACHINE_IA64;
	sf.AddrPC.Offset = c.StIIP;
	sf.AddrPC.Mode = AddrModeFlat;
	sf.AddrFrame.Offset = c.IntSp;
	sf.AddrFrame.Mode = AddrModeFlat;
	sf.AddrBStore.Offset = c.RsBSP;
	sf.AddrBStore.Mode = AddrModeFlat;
	sf.AddrStack.Offset = c.IntSp;
	sf.AddrStack.Mode = AddrModeFlat;
#else
#error "Platform not supported!"
#endif
	HANDLE hThread = GetCurrentThread();
	vector<CallStackInfo> arrCallStackInfo;
	while (true)
	{
		// 该函数是实现这个功能的最重要的一个函数
		// 函数的用法以及参数和返回值的具体解释可以查询MSDN
		if (!StackWalk64(dwImageType, hProcess, hThread, &sf, &c, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL))
		{
			break;
		}
		if (sf.AddrFrame.Offset == 0)
		{
			break;
		}
		CallStackInfo callstackinfo;
		memset(&callstackinfo, 0, sizeof(callstackinfo));
		BYTE symbolBuffer[sizeof(IMAGEHLP_SYMBOL64) + MAX_NAME_LENGTH];
		IMAGEHLP_SYMBOL64 *pSymbol = (IMAGEHLP_SYMBOL64*)symbolBuffer;
		memset(pSymbol, 0, sizeof(IMAGEHLP_SYMBOL64) + MAX_NAME_LENGTH);
		pSymbol->SizeOfStruct = sizeof(symbolBuffer);
		pSymbol->MaxNameLength = MAX_NAME_LENGTH;
		DWORD symDisplacement = 0;
		// 得到函数名
		if (SymGetSymFromAddr64(hProcess, sf.AddrPC.Offset, NULL, pSymbol))
		{
			strncpy_s(callstackinfo.MethodName, MAX_NAME_LENGTH, pSymbol->Name, _TRUNCATE);
		}
		IMAGEHLP_LINE64 lineInfo;
		memset(&lineInfo, 0, sizeof(IMAGEHLP_LINE64));
		lineInfo.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
		DWORD dwLineDisplacement;
		// 得到文件名和所在的代码行
		if (SymGetLineFromAddr64(hProcess, sf.AddrPC.Offset, &dwLineDisplacement, &lineInfo))
		{
			strncpy_s(callstackinfo.FileName, MAX_NAME_LENGTH, lineInfo.FileName, _TRUNCATE);
			sprintf_s(callstackinfo.LineNumber, "%d", lineInfo.LineNumber);
		}
		IMAGEHLP_MODULE64 moduleInfo;
		memset(&moduleInfo, 0, sizeof(IMAGEHLP_MODULE64));
		moduleInfo.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
		// 得到模块名
		if (SymGetModuleInfo64(hProcess, sf.AddrPC.Offset, &moduleInfo))
		{
			strncpy_s(callstackinfo.ModuleName, MAX_NAME_LENGTH, moduleInfo.ModuleName, _TRUNCATE);
		}
		arrCallStackInfo.push_back(callstackinfo);
	}
	SymCleanup(hProcess);
	return arrCallStackInfo;
}

// 创建Dump文件
//
void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
{
	// 创建Dump文件
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE != hDumpFile)
	{
		// Dump信息
		MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
		dumpInfo.ExceptionPointers = pException;
		dumpInfo.ThreadId = GetCurrentThreadId();
		dumpInfo.ClientPointers = TRUE;
		// 写入Dump文件内容
		//
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
		CloseHandle(hDumpFile);
	}
}

void PrintExceptionStackInfo(EXCEPTION_POINTERS *pException)
{
#ifdef _M_IX86
	if (pException->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
	{
		static char TempStack[1024 * 128];
		__asm mov eax, offset TempStack[1024 * 128];
		__asm mov esp, eax;
	}
#endif
	// 输出Crash信息 // 崩溃信息
	//
	cout << setbase(16) << setiosflags(ios::uppercase);
	cout << "ErrorCode: " << pException->ExceptionRecord->ExceptionCode << endl;
	cout << "Address : " << pException->ExceptionRecord->ExceptionAddress << endl;
	cout << "Flags : " << pException->ExceptionRecord->ExceptionFlags << endl;
	cout << endl;
	vector<CallStackInfo> arrCallStackInfo = GetCallStack(pException->ContextRecord);
	// 输出CallStack
	//
	cout << "*********************CallStack********************" << endl;
	for (vector<CallStackInfo>::iterator it = arrCallStackInfo.begin(); it != arrCallStackInfo.end(); ++it)
	{
		CallStackInfo callstackinfo = (*it);
		cout << callstackinfo.MethodName << "() , " << "@line:" << callstackinfo.LineNumber << " [" << callstackinfo.ModuleName << "]" << endl;
		cout << " (File: " << callstackinfo.FileName << ")" << endl;
	}
}

int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers, PWCHAR pwAppName)
{
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szFileName[MAX_PATH] = { 0 };
	TCHAR* szAppName = pwAppName;
	TCHAR* szVersion = L"v1.0";
	TCHAR dwBufferSize = MAX_PATH;
	SYSTEMTIME stLocalTime;

	GetModuleFileName(NULL, szPath, MAX_PATH);
	(_tcsrchr(szPath, _T('\\')))[1] = 0; // 删除文件名，只获得路径字串
	GetLocalTime(&stLocalTime);
	StringCchPrintf(szFileName, MAX_PATH, L"%s%s_%s-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp",
		szPath, szAppName, szVersion,
		stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
		stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond,
		GetCurrentProcessId(), GetCurrentThreadId());

	CreateDumpFile(szFileName, pExceptionPointers);
	PrintExceptionStackInfo(pExceptionPointers);
	FatalAppExit(-1, _T("*** Unhandled Exception! ***"));
	return EXCEPTION_EXECUTE_HANDLER;
}
// 处理Unhandled Exception的回调函数
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
	return GenerateMiniDump(pException, L"A4D Engine");
}

void RegisterCrashHandler()
{
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
}