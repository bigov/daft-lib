#include <iostream>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

using namespace std;

////////
// обрезает строку "stringp" по первому найденному символу
// из числа указаных в "delim"
//
char * strsep(char **stringp, const char *delim)
{
	char *p;
	
	if(!stringp)
		return(NULL);
	p=*stringp;
	while(**stringp && !strchr(delim,**stringp))
		(*stringp)++;
	if(**stringp)
	{
		**stringp='\0';
		(*stringp)++;
	}
	else
		*stringp=NULL;
	return(p);
}

int main()
{
	char msg[] = "test|ing mes|sage";
	cout << "msg: " << msg << endl;
	char *p;
	p = msg;
	char * f = strsep(&p, ",| ");	
	cout << "f: " << f << endl;

	return 0;
}

