#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

char ErrStr[0]; 	// Текс сообщения об ошибке

// Функция прерывания программы из библиотеки stdlib.h
void exit(int);

/**
 * Возвращает 1 (true), если есть сообщения об ошибках
 */
bool NoErrors(void)
{
  if (strlen(ErrStr)) return false;
  else return true;
}
/**
 * Очистка строки ошибок
 */
void ClearErrors(void)
{
  memset(ErrStr, '\0', strlen(ErrStr));
  return;
}

int main(int argc, char* argv[])
{
    // отображение текущего времени в системе
    const time_t timer = time(NULL);
    printf("%s\n", ctime(&timer));

    strcat(ErrStr, "First message.");
    strcat(ErrStr, "\nMy second message.");
    fprintf(stderr, "Std Err: %s", ErrStr);
    strcat(ErrStr, " Final message.");

    printf("\n\nErrStr: %s\nErrLen: %i\n\n", ErrStr, strlen(ErrStr));

    ClearErrors();
    strcat(ErrStr, "New message");
    printf("ErrStr: %s\nErrLen: %i\n\n", ErrStr, strlen(ErrStr));
    if(NoErrors()) printf("No error messages\n");

    float t = clock();
    fprintf(stdout, "job time: %f(sec)\n", t/CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}
