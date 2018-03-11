#!/usr/bin/env python
# -*- coding:utf-8 -*-

import time
import math

import pyglet
from _ast import Str
pyglet.options['debug_gl'] = True
from pyglet.gl import *
from pyglet.window import key
from packer import *
import space
from layout import Camera


def setup_light():
    ''' Параметры источников света

        ambient - фоновый (всенаправленный)
        difuuze - диффузный направленный
        specular - зеркальный
    '''
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE)

    # основной - желтоватый
    glLightfv(GL_LIGHT0, GL_DIFFUSE, (GLfloat * 4)(1.45, 1.45, 1.30, 1.00))
    glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat * 4)(0.30, 0.30, 0.30, 1.00))
    glLightfv(GL_LIGHT0, GL_SPECULAR,(GLfloat * 4)(0.30, 0.30, 0.30, 1.00))
    # задняя подсветка - серая
    glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat * 4)(1.0, 1.0, 1.0, 1.0))
    glLightfv(GL_LIGHT1, GL_AMBIENT, (GLfloat * 4)(0.0, 0.0, 0.0, 1.0))
    glLightfv(GL_LIGHT1, GL_SPECULAR,(GLfloat * 4)(0.0, 0.0, 0.0, 1.0))

    glLightfv(GL_LIGHT0, GL_POSITION, glType(GLfloat, -6.0, 6.40, -5.5, 0.0))
    glLightfv(GL_LIGHT1, GL_POSITION, glType(GLfloat, 5.0, -2.5, 6.0, 0.0))

    glEnable(GL_LIGHT0)
    glEnable(GL_LIGHT1)


def set_2d():
    """ Configure OpenGL to draw in 2d.
    """
    width, height = window.get_size()
    glDisable(GL_DEPTH_TEST)
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0, width, 0, height, -1, 1)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glDisable(GL_LIGHTING)

def set_3d():
    """ Configure OpenGL to draw in 3d.
    """
    glEnable(GL_DEPTH_TEST)
    glDepthFunc(GL_LESS)
    glEnable(GL_LIGHTING)

    # Не отображать задние поверхности плоскостей
    glEnable(GL_CULL_FACE)
    glFrontFace(GL_CCW)

    width, height = window.get_size()
    glViewport(0, 0, width, height)

    glMatrixMode(GL_PROJECTION | GL_MODELVIEW)
    glLoadIdentity()
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    gluPerspective(70.0, window.width / window.height, 0.1, 60.0)

platform = pyglet.window.get_platform()
display = platform.get_default_display()
screen = display.get_default_screen()
config = screen.get_best_config()
context = config.create_context(None)
win_cfg = {'config': config, 'width': 1920, 'height': 1080, 'visible': True, 'fullscreen': True, 'resizable': False}
#win_cfg = {'config': config, 'width': 1024, 'height': 768, 'visible': True, 'fullscreen': False, 'resizable': False}
window = pyglet.window.Window(context=context, **win_cfg)

color_sky = [0.5, 0.69, 1.0, 1]
glClearColor(*color_sky)
window.clear()
window.set_exclusive_mouse(True)


set_2d()
set_3d()

camera = Camera()
world = space.World()

# замер времени генерации пространства
#s = time.time()
world.gen_space((0, 0, 0), camera.azim, camera.zenit)
#e = time.time()
# вывод времени генерации пространства
#print('gen_space', round(e - s, 3), 'sec')
#del(e,s)
setup_light()

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
glEnable(GL_BLEND)

label = pyglet.text.Label('WWW',
    font_name='Tahoma',
    font_size=14,
    color=(55, 55, 255, 255),
    x=20, y=window.height - 20,
    anchor_x='left', anchor_y='top')

@window.event
def on_draw():
    set_3d()
    gluLookAt(*camera.LookSet)
    world.gen_space((0, 0, 0), camera.azim, camera.zenit)
    ''' Один добавленые в пакет world.batch грани это не стирает, но оценить
    скорость прорисовки пространства с включеной опцией контроля пирамиды
    видимости дает возможность. 
    '''
    window.clear()
    world.batch.draw()
    set_2d()
    info_quad(window.height, 320, 40)
    text = 'azim: ' + str('%+1f' % round(camera.azim, 3)) 
    text += ', zenit: ' + str('%+1f' % round(camera.zenit, 3)) 
    label.text = text
    label.draw()

@window.event
def on_mouse_motion(x, y, dx, dy):
    camera.turn_look(x, y, dx, dy)


@window.event
def on_key_press(symbol, modifiers):
    if (symbol == key.ESCAPE):
        window.set_exclusive_mouse(False)
    else:
        camera.key_press(symbol, modifiers)


@window.event
def on_key_release(symbol, modifiers):
    camera.key_release(symbol, modifiers)


@window.event
def on_resize(width, height):
    pass


pyglet.clock.schedule(camera.stream)
pyglet.app.run()

