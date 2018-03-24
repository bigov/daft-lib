/**
 *  mydir.cpp: Определение каталога, в котором расположена программа
 *
 *  !!! MS-Windows ONLY !!!
 */

//#include "stdafx.h"
//#include "windows.h"
#include <direct.h>

void main()
{
	TCHAR buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer),buffer);
	cout << buffer << endl;
	SetCurrentDirectory("C:\\");
	GetCurrentDirectory(sizeof(buffer),buffer);
	cout << buffer << endl;
}

