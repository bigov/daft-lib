#include <stdio.h>
#include <string.h>

void logErr(char** s, int n)
{
  int idx = 0;
  while (n > idx) printf("%s", s[idx++]);
  printf("\n\n");
  return;
}

int main(void)
{
  char* fname = "myFile.ext";
  char* carr[4] = {
    "\nmsg ",
    fname,
    "Hi, sir!",
    "gogo" };
  logErr(carr, 4);
  return 0;
}

