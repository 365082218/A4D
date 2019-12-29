#include "stdafx.h"
#include "Console.h"
#pragma warning(disable:4996)
Console::Console()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	SetConsoleTitle(_T("W4D调试口"));
}


Console::~Console()
{
}
