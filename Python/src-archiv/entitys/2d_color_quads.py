#!/usr/bin/env python
"""
2D сущности в виде цветных квадратов

Создание словаря {"one": 1, "two": 2, "three": 3}:

    >>> a = dict(one=1, two=2, three=3)
    >>> b = {'one': 1, 'two': 2, 'three': 3}
    >>> c = dict(zip(['one', 'two', 'three'], [1, 2, 3]))
    >>> d = dict([('two', 2), ('one', 1), ('three', 3)])
    >>> e = dict({'three': 3, 'one': 1, 'two': 2})
    >>> a == b == c == d == e
    True
"""

from random import random
from pyglet.gl import *
import pyglet
from pyglet.window import key


class Quad(object):

    width = 50.0
    height = 50.0

    def __init__(self):

        x = random() * (window.width - self.width)
        y = random() * (window.height - self.height)

        r = random()
        g = random()
        b = random()

        self.point = (x, y) # координаты точки в пространстве
        self.obj = space_batch.add(4, GL_QUADS, None,
            ('v2f', (x, y, x+self.width, y, x+self.width, y+self.height, x, y+self.height)),
            ('c4f', (r, g, b, 0.8)*4))

        #print(self.point)


    def delete(self):
        """Удаляет графический объект из пакета отображения batch
        :return: void
        """
        self.obj.delete()
        #print("removed (%f, %f)" % self.point)


    def update(self, dt):
        """ Изменим цвет случайтным образом

        :param dt:
        :return: Void
        """
        r = random()
        g = random()
        b = random()
        self.obj.delete()
        (x, y) = self.point
        self.obj = space_batch.add(4, GL_QUADS, None,
            ('v2f', (x, y, x+self.width, y, x+self.width, y+self.height, x, y+self.height)),
            ('c4f', (r, g, b, 0.8)*4))


window = pyglet.window.Window(1024, 768)


@window.event
def on_key_press(symbol, modifiers):
    if symbol == key.SPACE:
        q = Quad()
        all_quads[q.point] = q
    elif symbol == key.BACKSPACE:
        # если словать не пустой - извлечь один элемент
        if all_quads:
            (point, obj) = all_quads.popitem()
            obj.delete()
            del(point, obj)
    elif symbol == key.ESCAPE:
        window.has_exit = True


@window.event
def on_draw():
    window.clear()
    space_batch.draw()
    label.draw()


def space_update(dt):

    if all_quads:
        (point, obj) = all_quads.popitem()
        #obj.update(dt)
        all_quads[point] = obj

pyglet.clock.schedule_interval(space_update, 1/30.)
pyglet.gl.glClearColor(0.5, 1.0, 0.5, 1.0)
space_batch = pyglet.graphics.Batch()
#all_quads = {}
all_quads = dict()
label = pyglet.text.Label('Press [ SPACE ] to add a object, [<-Backspace] to remove',
                          font_size=14,
                          x=window.width // 2, y=10,
                          anchor_x='center')

if __name__ == '__main__':
    pyglet.app.run()