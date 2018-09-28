////////////////
//
//	Перенаправление потока ввод на прием из файла и
// посимвольный ввод (широкие символы принимает "по-частям")
//

// get file buffer size using in_avail
#include <stdio.h>
#include <termios.h>

int main(void)
{
	struct termios ti;
	int c;

	tcgetattr(0, &ti);
	
	ti.c_lflag &= (unsigned)(~ICANON);
	ti.c_lflag &= (unsigned)(~ECHO);
	
	tcsetattr(0, TCSANOW, &ti);

	//printf("Press Ctrl-D to exit\n");

	while((c = getchar()) != '\n')
		printf("Got: '%c' (%d)\n", c, c);

	ti.c_lflag |= ICANON | ECHO;
	tcsetattr(0, TCSANOW, &ti);

	return 0;
}
