#!/usr/bin/env python
#
#-*- coding:utf-8 -*-

import pyglet
pyglet.options['debug_gl'] = True
from pyglet.gl import *
from pyglet.window import key

import space
from layout import Camera


class Config(object):
    def __init__(self):
        self.x = 0
        self.y = 0
        self.z = 0
        self.speed = 4
        # Светло-голубой
        self.color_0 = [0.5, 0.69, 1.0, 1]
        self.look = (0, 0)

        self.strafe = [0, 0]
        self.position = (0, -1, -1)

cfg = Config()

platform = pyglet.window.get_platform()
display = platform.get_default_display()
screen = display.get_default_screen()
config = screen.get_best_config()
context = config.create_context(None)
win_cfg = {'config': config, 'width': 1000, 'height': 800,
    'visible': True, 'resizable': True}
window = pyglet.window.Window(context=context, **win_cfg)
window.clear()
glClearColor(*cfg.color_0)

labels = pyglet.text.Label('X', font_name='Verdana', font_size=22,
    color=(0, 0, 0, 255), x=10, y=10, anchor_x='left', anchor_y='center')

window.set_exclusive_mouse(True)

camera = Camera()
world = space.World()

#from model import Model
#db = Model()


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
def on_draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_PROJECTION | GL_MODELVIEW)
    glEnable(GL_DEPTH_TEST)

    # Режим бесшовного наложения тестур
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)

    glLoadIdentity()
    gluPerspective(64, window.width / window.height, 0.1, 150.0)
    #glTranslatef(*move.Translate)
    #glRotatef(*move.Rotate)
    gluLookAt(*camera.LookSet)
    world.batch.draw()


@window.event
def on_resize(width, height):
    pass

pyglet.clock.schedule(camera.stream)
pyglet.app.run()
