#-*- coding:utf-8 -*-
''' список, заполненный случайными числами от 1 до 9 (используя функцию
randint из модуля random):
    A = [ randint(1, 9) for i in range(n)]

Ячейки 9x9: по 81-й ячейке в стопке из 9 слоев
или
    колонка из 9 ячеек
    №^10 | 2^2
    -----+-----
      1  | 1
      2  | 2
      3  | 4
      4  | 8
      5  | 16
      6  | 32
      7  | 64
      8  | 128
      9  | 256
    -----------
          512 - все заполнены
          257 - только верхняя и нижняя

    модель кубика:
        cube = [512] * 9

    Индекс элементов:
    1 - камень
    2 - земля
'''

import sqlite3


class Model(object):

    def __init__(self):
        ''' Координаты блока - x,y,z и az - азимут (направление)
        '''

        db = sqlite3.connect(":memory:")
        db.isolation_level = None
        cur = db.cursor()
        cur.execute(''' CREATE TABLE world(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                x INTEGER, y INTEGER, z INTEGER, az INTEGER,
                ent_id INTEGER);''')
        cur.execute('''CREATE TABLE ents(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name STRING,
                img_top BLOB,
                img_bottom BLOB DEFAULT NULL,
                img_face BLOB DEFAULT NULL,
                img_back BLOB DEFAULT NULL,
                img_left BLOB DEFAULT NULL,
                img_right BLOB DEFAULT NULL,
                weight INTEGER,
                bright INTEGER,
                transp INTEGER);''')

        db.commit()
        db.close()

    def location(self):
        ''' возвращает текущие координаты положения камеры
        '''
        pass

    def add_cell(self, p):
        ''' Добавление элемента в структура
        '''
        pass

    def remove_cell(self, p):
        ''' Удаление элемента из структуры
        '''
        pass

    def get_cell(self, p):
        ''' Генератор ячейки в виде пустого кубика 9x9x9
            содержит массив из 81 числа, описывающий 9x9 матрицу из колонок
            по 9 элементов каждая.
        '''
        pass

    def save_data(self):
        ''' Сохранени данных структуры в базе данных
        '''
        pass

    def load_data(self):
        ''' Загрузка данных из базы
        '''
        pass
