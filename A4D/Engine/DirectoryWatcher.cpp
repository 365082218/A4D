#include "stdafx.h"
#include "DirectoryWatcher.h"

DirectoryWatcher::DirectoryWatcher()
{
	watchD = NULL;
	watchT = NULL;
	dwThreadId = 0;
	bWaitExit = false;
}


DirectoryWatcher::~DirectoryWatcher()
{

}

void DirectoryWatcher::Exit()
{
	if (watchD != NULL && watchD != INVALID_HANDLE_VALUE)
		CloseHandle(watchD);
	if (watchT != NULL && watchT != INVALID_HANDLE_VALUE)
		CloseHandle(watchT);
	watchD = NULL;
	watchT = NULL;
	dwThreadId = NULL;
	bWaitExit = false;
}

DWORD WINAPI DirectoryWatcher::Monitor(
	LPVOID lpThreadParameter
)
{
	DirectoryWatcher * pWatcher = (DirectoryWatcher *)lpThreadParameter;
	HANDLE watchH = pWatcher->watchD;

	DWORD cbBytes;
	char file_name[MAX_PATH]; //�����ļ���;
	char file_rename[MAX_PATH]; //�����ļ��������������;
	char notify[1024];
	int count = 0; //�ļ�����������ͬʱ������ɾ������ļ������Խ��и��Ѻõ���ʾ;

	memset(notify, 0, strlen(notify));
	FILE_NOTIFY_INFORMATION *pnotify = (FILE_NOTIFY_INFORMATION*)notify;

	cout << "Start Monitor..." << endl;

	while (true)
	{
		if (pWatcher->WantExit())
			break;
		if (ReadDirectoryChangesW(watchH, &notify, 1024, true,
			FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE,
			&cbBytes, NULL, NULL))
		{
			//ת���ļ���Ϊ���ֽ��ַ���;
			if (pnotify->FileName)
			{
				memset(file_name, 0, strlen(file_name));
				WideCharToMultiByte(CP_ACP, 0, pnotify->FileName, pnotify->FileNameLength / 2, file_name, 99, NULL, NULL);
			}

			//��ȡ���������ļ���;
			if (pnotify->NextEntryOffset != 0 && (pnotify->FileNameLength > 0 && pnotify->FileNameLength < MAX_PATH))
			{
				PFILE_NOTIFY_INFORMATION p = (PFILE_NOTIFY_INFORMATION)((char*)pnotify + pnotify->NextEntryOffset);
				memset(file_rename, 0, sizeof(file_rename));
				WideCharToMultiByte(CP_ACP, 0, p->FileName, p->FileNameLength / 2, file_rename, 99, NULL, NULL);
			}

			//�������͹�����,�����ļ����������ġ�ɾ������������;
			switch (pnotify->Action)
			{
			case FILE_ACTION_ADDED:
				count++;
				cout << "count  = " << count << endl;
				cout << setw(5) << "file add:" << setw(5) << file_name << endl;
				break;

			case FILE_ACTION_MODIFIED:
				cout << "file modified:" << setw(5) << file_name << endl;
				break;

			case FILE_ACTION_REMOVED:
				count++;
				cout << count << setw(5) << "file removed:" << setw(5) << file_name << endl;
				break;

			case FILE_ACTION_RENAMED_OLD_NAME:
				cout << "file renamed:" << setw(5) << file_name << "->" << file_rename << endl;
				break;

			default:
				cout << "UNknow command!" << endl;
			}
		}
	}
	pWatcher->Exit();
	return 0;
}

bool DirectoryWatcher::Watch(TCHAR * dir)
{
	if (watchD != NULL || watchT != NULL)
		return false;
	lstrcpyW(directory, dir);

	watchD = CreateFile(directory,
		GENERIC_READ | GENERIC_WRITE | FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);

	if (watchD == INVALID_HANDLE_VALUE) //�������ض����Ŀ���ļ�ϵͳ��֧�ָò���������ʧ�ܣ�ͬʱ����GetLastError()����ERROR_INVALID_FUNCTION
	{
		cout << "error" + GetLastError() << endl;
		return false;
	}

	::CreateThread(NULL, 0, DirectoryWatcher::Monitor, this, 0, &dwThreadId);
	return true;
}
