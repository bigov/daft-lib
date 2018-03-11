#!/usr/bin/env python
# -*- coding:utf-8 -*-

import pyglet
from pyglet.gl import *

platform = pyglet.window.get_platform()
display = platform.get_default_display()
screen = display.get_default_screen()
config = screen.get_best_config()
context = config.create_context(None)
win_cfg = {'config': config, 'width': 800, 'height': 600,
    'visible': True, 'fullscreen': False, 'resizable': False}
window = pyglet.window.Window(context=context, **win_cfg)

glClearColor(0.5, 0.69, 1.0, 1)
window.clear()

def tex_coord(x, y):
    """ Привязка вершин к текстуре через указание номера строки и колонки
    """
    # количество текстур в файле
    n = 4.0
    m = 1.0 / n
    dx = x * m
    dy = y * m

    return dx, dy, dx + m, dy, dx + m, dy + m, dx, dy + m

def cube(self, x, y, z):
    ''' Генератор координат куба
    '''
    y0 = (y - 0.5)
    y1 = (y + 0.5)
    x0 = (x - 0.50)
    x1 = (x + 0.50)
    z0 = (z - 0.50)
    z1 = (z + 0.50)

    # (Top)(Down)(Face)(Right)(Back)(Left)
    t = [x0, y1, z1, x1, y1, z1, x1, y1, z0, x0, y1, z0]
    d = [x0, y0, z0, x1, y0, z0, x1, y0, z1, x0, y0, z1]
    f = [x0, y0, z1, x1, y0, z1, x1, y1, z1, x0, y1, z1]
    r = [x1, y0, z1, x1, y0, z0, x1, y1, z0, x1, y1, z1]
    b = [x1, y0, z0, x0, y0, z0, x0, y1, z0, x1, y1, z0]
    l = [x0, y0, z0, x0, y0, z1, x0, y1, z1, x0, y1, z0]
    cube = r + l + d + t + b + f
    return cube

tX = tex_coord(0, 3)
tY = tex_coord(1, 3)
tZ = tex_coord(2, 3)



glViewport(0,0, window.width, window.height)   #Reset The Current Viewport
glMatrixMode(GL_PROJECTION | GL_MODELVIEW)     #Select The Projection Matrix
glLoadIdentity()                               #Reset The Matrix

pyglet.app.run()
