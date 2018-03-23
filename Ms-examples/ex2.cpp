//
//
// Example 2
//
// Altering the environment variables of a child process during process
// creation is the only way one process can directly change the environment
// variables of another process. A process can never directly change the
// environment variables of another process that is not a child of that
// process.
//
// If you want the child process to inherit most of the parent's environment 
// with only a few changes, retrieve the current values using
// GetEnvironmentVariable, save these values, create an updated block for the
// child process to inherit, create the child process, and then restore the
// saved values using SetEnvironmentVariable, as shown in the following
// example.
//
// This example uses the code in example three as the child process, Ex3.exe


#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define BUFSIZE 4096
#define VARNAME TEXT("MyVariable")

int _tmain()
{
    DWORD dwRet, dwErr;
    LPTSTR pszOldVal; 
    TCHAR szAppName[]=TEXT("ex3.exe");
    DWORD dwFlags=0;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    BOOL fExist, fSuccess; 
 
    // Retrieves the current value of the variable if it exists.
    // Sets the variable to a new value, creates a child process,
    // then uses SetEnvironmentVariable to restore the original
    // value or delete it if it did not exist previously. 
 
    pszOldVal = (LPTSTR) malloc(BUFSIZE*sizeof(TCHAR));
    if(NULL == pszOldVal)
    {
        printf("Out of memory\n");
        return FALSE;
    }

    dwRet = GetEnvironmentVariable(VARNAME, pszOldVal, BUFSIZE);

    if(0 == dwRet)
    {
        dwErr = GetLastError();
        if( ERROR_ENVVAR_NOT_FOUND == dwErr )
        {
            printf("Environment variable does not exist.\n");
            fExist=FALSE;
        }
    }
    else if(BUFSIZE < dwRet)
    {
        pszOldVal = (LPTSTR) realloc(pszOldVal, dwRet*sizeof(TCHAR));   
        if(NULL == pszOldVal)
        {
            printf("Out of memory\n");
            return FALSE;
        }
        dwRet = GetEnvironmentVariable(VARNAME, pszOldVal, dwRet);
        if(!dwRet)
        {
            printf("GetEnvironmentVariable failed (%d)\n", GetLastError());
            return FALSE;
        }
        else fExist=TRUE;
    }
    else fExist=TRUE;

    // Set a value for the child process to inherit. 
 
    if (! SetEnvironmentVariable(VARNAME, TEXT("Test"))) 
    {
        printf("SetEnvironmentVariable failed (%d)\n", GetLastError()); 
        return FALSE;
    }
 
    // Create a child process. 

    SecureZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
 
#ifdef UNICODE
    dwFlags = CREATE_UNICODE_ENVIRONMENT;
#endif

    fSuccess = CreateProcess(szAppName, NULL, NULL, NULL, TRUE, dwFlags, 
        NULL,     // inherit parent's environment 
        NULL, &si, &pi); 
    if (! fSuccess) 
    {
        printf("CreateProcess failed (%d)\n", GetLastError()); 
    }
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Restore the original environment variable. 
 
    if(fExist)
    {
        if (! SetEnvironmentVariable(VARNAME, pszOldVal)) 
        {
            printf("SetEnvironmentVariable failed (%d)\n", GetLastError()); 
            return FALSE;
        }
    }
    else SetEnvironmentVariable(VARNAME, NULL);

    free(pszOldVal);
    
    return fSuccess;
}

