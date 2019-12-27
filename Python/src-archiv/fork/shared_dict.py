""" Демонстрация одновременной работы двух процессов с одним словарем:

    - основной процесс последовательно добавляет элементы в общий словарь и
      выводит на печать все текущие значения словаря

    - дочерний процесс удаляет избранные элементы из словаря и выводит их
      на печать.
"""

from multiprocessing import Process, Manager
import time

def ch(d):
    for j in range(10):
       k = j*2
       x = d.pop(k)
       print("removed (%i: %i)" % (k, x))
       time.sleep(3)


if __name__ == '__main__':

    manager = Manager()
    d = manager.dict()
    d['a'] = 111

    p = Process(target=ch, args=(d,))
    p.start()

    for i in range(10):
        d[i] = i**2
        print(d)
        time.sleep(1)

    if p.is_alive():
        p.terminate()

    print(d)
