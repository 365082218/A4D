#pragma once
#include "EventDispatcher.h"
class DirectoryWatcher:public EventDispatcher
{
	DirectoryWatcher();
public:
	~DirectoryWatcher();
	TCHAR directory[MAX_PATH];
	bool Watch(TCHAR * path);
	HANDLE watchD;//Ä¿Â¼¾ä±ú
	HANDLE watchT;//Ïß³Ì¾ä±ú
	DWORD dwThreadId;
	static DWORD WINAPI DirectoryWatcher::Monitor(
		LPVOID lpThreadParameter
	);
	bool bWaitExit;
	bool WantExit() { return bWaitExit; }
	void Exit();
};

