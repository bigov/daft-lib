//
// Запуск Emacs c окном нужного размера
// Компилируется:
//  clang++ ex1.cpp -mwindows -Wl,-subsystem,windows -o emacsrun.exe
//
#include <windows.h>
#include <tchar.h>

int _tmain()
{
    DWORD dwFlags=0;
    TCHAR szApp[]=TEXT("runemacs.exe -g 120x60\0");
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    BOOL fSuccess; 
 
    // Create the child process, specifying a new environment block. 
    SecureZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

#ifdef UNICODE
    dwFlags = CREATE_UNICODE_ENVIRONMENT;
#endif

    fSuccess = CreateProcess(NULL, szApp, NULL, NULL, FALSE, dwFlags,
        NULL, NULL, &si, &pi); 
 
    if (! fSuccess) return FALSE;
    WaitForSingleObject(pi.hProcess, INFINITE);
    return TRUE;
}

