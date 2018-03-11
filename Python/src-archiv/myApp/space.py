# -*- coding:utf-8 -*-

import pyglet
from pyglet.gl import *
from pyglet.image.codecs.bmp import BMPImageDecoder
from random import randrange
from itertools import product

import tricks
import rig


class Unit(object):
    """ Базовые элементы виртуального пространства
    """

    def __init__(self, point, texture_id):
        """
        :param point: position in the 3D environment
        :return: void
        """

        # TODO: реализовать назначение текстур по индексу типа элемента

        self.point = point
        self.texture_id = texture_id
        self.flats = self.calc_flats(point, texture_id)

        # координаты выбранных для отображения граней отдаем в OpenGL
        self.batched = rig.space_batch.add(*self.flats)

    def update(self):
        """ Обновить отображаемые грани, если изменился их состав
        :return: Void
        """

        # TODO: проверять расстояние до камеры и удалять объекты за пределами активной зоны.

        new_flats = self.calc_flats(self.point, self.texture_id)
        if not new_flats == self.flats:
            self.batched.delete()
            self.batched = rig.space_batch.add(*new_flats)
            self.flats = new_flats

    def delete(self):
        """ Удаление элемента
        """
        x, y, z = self.point
        self.batched.delete()
        near = ((x+1, y, z), (x-1, y, z), (x, y+1, z), (x, y-1, z), (x, y, z+1), (x, y, z-1))
        for point in near:
            u = rig.active_units.get(point)
            if u:
                u.update()

    def calc_flats(self, point, texture_id):
        """ Проверяем наличие соседнего элемента перед гранью, и если рядом пусто - строим грань.
        :return: flats tuple
        """

        (x, y, z) = point
        h = rig.height_to_length

        y0 = (y - 0.5) * h
        y1 = (y + 0.5) * h

        x0 = x - 0.50
        x1 = x + 0.50

        z0 = z - 0.50
        z1 = z + 0.50

        q = []  # массив точек координат вершин граней
        t = []  # координаты текстур
        n = []  # нормали к граням

        texture = rig.textures[texture_id]

        # right
        if not (x - 1, y, z) in rig.active_units:
            q.extend((x0, y0, z0, x0, y0, z1, x0, y1, z1, x0, y1, z0))
            t.extend(texture[0])
            n.extend((-1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0))
        # left
        if not (x + 1, y, z) in rig.active_units:
            q.extend((x1, y0, z1, x1, y0, z0, x1, y1, z0, x1, y1, z1))
            t.extend(texture[1])
            n.extend((1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0))
        # down
        if not (x, y - 1, z) in rig.active_units:
            q.extend((x0, y0, z0, x1, y0, z0, x1, y0, z1, x0, y0, z1))
            t.extend(texture[2])
            n.extend((0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0))
        # top
        if not (x, y + 1, z) in rig.active_units:
            q.extend((x0, y1, z1, x1, y1, z1, x1, y1, z0, x0, y1, z0))
            t.extend(texture[3])
            n.extend((0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0))
        # back
        if not (x, y, z - 1) in rig.active_units:
            q.extend((x1, y0, z0, x0, y0, z0, x0, y1, z0, x1, y1, z0))
            t.extend(texture[4])
            n.extend((0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0))
        # face
        if not (x, y, z + 1) in rig.active_units:
            q.extend((x0, y0, z1, x1, y0, z1, x1, y1, z1, x0, y1, z1))
            t.extend(texture[5])
            n.extend((0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0))

        # список координат всех выбранных для отображения граней
        return int(len(q) / 3), GL_QUADS, rig.TextureGroup, ('v3f', q), ('t2f', t), ('n3f', n)


class World(object):
    """ Генератор пространства
    """

    def __init__(self):

        # Загрузить файл изображения текстур
        bmp = pyglet.image.codecs.bmp.BMPImageDecoder()
        img = pyglet.image.load(rig.textures_filename, decoder=bmp).get_texture()
        rig.TextureGroup = pyglet.graphics.TextureGroup(img)

        rig.textures[0] = tricks.get_texture_coordinates((1.0, 1.0), (1.0, 1.0), (1.0, 1.0))
        rig.textures[1] = tricks.get_texture_coordinates((2.0, 1.0), (1.0, 1.0), (1.0, 0.0))

        glClearColor(0.5, 0.69, 1.0, 1)

        """
        # генерируем мипмап текстур
        glGenerateMipmap(GL_TEXTURE_2D)
        # Когда изображение увеличивается используем обычную фильтрацию
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
        # Когда изображение уменьшается, то используем смешивание 2х мипмапов,
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR)
        # Трилинейная фильтрация.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
        """

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)

        # Начальное заполнение пространства - три слоя грунта (верхний с травой)
        textures_id = (1, 0, 0)
        for x, z in product(range(-20, 20), range(-20, 20)):
            y = randrange(2)
            # три точки вертикально друг-над-другом
            rig.active_units.update(dict(zip(((x, y, z), (x, y-1, z), (x, y-2, z)), textures_id)))


    def draw(self):
        rig.space_batch.draw()
