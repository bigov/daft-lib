/**
 * Для указателей и массивов выделяем память при помощи оператора
 *
 *		new
 *
 * Освобождение выделенной памяти произвоится операциями "delete x" для
 * указателя, и "delete[] x" для массива.
 *
 * Если в системе свободная память "кучи" исчерпана, то вызов "new"
 * сгенерирует стандартное исключение
 *
 *		bad_alloc
 *
 * Чтобы не строить конструкцию "try-catch" при каждом вызове "new" имеется
 * стандартная функция
 *
 *		set_new_handler()
 *
 * которая поволяет устанавить свой обработчик. Например:
 */
#include <iostream>
#include <new>

void out_of_mem()
{
	std::cerr << "operator new failed: out of memory\n";
	throw std::bad_alloc();
}

int main()
{
	std::set_new_handler(out_of_mem);
	// тестируем работу
	for(;;) new char[10000];
	std::cout << "done\n";
}
/**
 * Хотя у меня на рабочем Archlinux процесс был убит системой, а обработчик
 * не сработал.
 */
