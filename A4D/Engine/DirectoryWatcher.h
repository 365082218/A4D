#pragma once
#include "EventDispatcher.h"
class DirectoryWatcher:public EventDispatcher
{
	DirectoryWatcher();
public:
	~DirectoryWatcher();
	TCHAR directory[MAX_PATH];
	bool Watch(TCHAR * path);
	HANDLE watchD;//Ŀ¼���
	HANDLE watchT;//�߳̾��
	DWORD dwThreadId;
	static DWORD WINAPI DirectoryWatcher::Monitor(
		LPVOID lpThreadParameter
	);
	bool bWaitExit;
	bool WantExit() { return bWaitExit; }
	void Exit();
};

