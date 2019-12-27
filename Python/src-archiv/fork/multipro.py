from multiprocessing import Process
import time


def sub1(txt):
    for i in range(30):
        time.sleep(1)
        print(txt, i)
    del(i)


def main(p):
    for j in range(4):
        time.sleep(2)
        print('main', j)
    del(j)

    if p.is_alive():
        p.terminate()
        time.sleep(0.1)
        print("beep terminated.")
    else:
        print("beep finished.")


if __name__ == '__main__':
    p = Process(target=sub1, args=("beep",))
    p.start()
    main(p)
    print('Main finished.')

''' Процессы можно создавать из обычных функций. Методы работы с процессами
почти все те же самые, что и для потоков из модуля threading. А вот для
синхронизации процессов и обмена данными принято использовать другие
инструменты. Речь идет об очередях (Queue) и каналах (Pipe).

Впрочем, аналоги локов, событий и семафоров, которые были в threading, здесь
тоже есть. Кроме того в модуле multiprocessing есть механизм работы с общей
памятью. Для этого в модуле есть классы переменной (Value) и массива (Array),
которые можно “обобщать” (share) между процессами. Для удобства работы с
общими переменными можно использовать классы-менеджеры (Manager). Они более
гибкие и удобные в обращении, однако более медленные. Нельзя не отметить
приятную возможность делать общими типы из модуля ctypes с помощью модуля
multiprocessing.sharedctypes.

Еще в модуле multiprocessing есть механизм создания пулов процессов. Этот
механизм очень удобно использовать для реализации шаблона Master-Worker или
для реализации параллельного Map (который в некотором смысле является частным
случаем Master-Worker).'''
