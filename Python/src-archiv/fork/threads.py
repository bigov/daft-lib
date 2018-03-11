import threading

def writer(x, event_for_wait, event_for_set):
    for i in range(5):
        event_for_wait.wait() # wait for event
        event_for_wait.clear() # clean event for future
        print(x)
        event_for_set.set() # set event for neighbor thread

# События управления потоками
e1 = threading.Event()
e2 = threading.Event()
e3 = threading.Event()

# Инициализация потоков
t1 = threading.Thread(target=writer, args=(1, e1, e2))
t2 = threading.Thread(target=writer, args=(2, e2, e3))
t3 = threading.Thread(target=writer, args=('3 \n', e3, e1))

# Запуск потоков
t1.start()
t2.start()
t3.start()

e3.set() # С какого потока начинать перебор

# join threads to the main thread
# PS тут не понял назначение
t1.join()
t2.join()
t3.join()
