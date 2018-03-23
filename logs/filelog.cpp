//
// пример работы с файлами
// http://cppstudio.com/post/446/
//

#include <cstdio>
#include <iostream>
#include <fstream>

using std::ios_base;
using std::ofstream;
using std::ifstream;

int main () {
	const char *logFileName = "log.txt";
	ofstream flog;

	// Определение размера файла
	FILE *ptrFile = fopen(logFileName, "rb");
	if (ptrFile == NULL)
		perror ("Ошибка открытия файла");
	else {
		fseek(ptrFile, 0, SEEK_END); // переместить указатель в конец файла
		long fsize = ftell(ptrFile);  // считать текущее положение указателя
		fclose (ptrFile);            // закрыть файл
		std::cout << "filesize file.txt: " << fsize << " byte\n";
	}

	// попытаться создать/обрезать файл журнала
	flog.open (logFileName, ios_base::out | ios_base::trunc);
	if(!flog.is_open()) {
		std::cerr << "FAILURE: can't open logfile." << std::endl;
		return 1; //exit failure
	}
	flog.close();

	// попытаться прочитать созданный ранее файл
	flog.open (logFileName, ios_base::in);
	if(!flog.is_open()) {
		std::cerr << "FAILURE: can't create logfile." << std::endl;
		return 1; //exit failure
	}
	flog.close();

	//Записать данные
	flog.open (logFileName, ios_base::app);
	flog << "Удивительные вещи" << std::endl;
	flog << "творятся в этом" << std::endl;
	flog << "удивительном мире" << std::endl;
	flog.close();

	return 0;
}
