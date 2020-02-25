#!/usr/bin/env python
# -*- coding:utf-8 -*-

import pyglet
pyglet.options['debug_gl'] = True
from pyglet.gl import *
from pyglet.window import key
from packer import *

import space
from layout import Camera


def glType(typ, *args):
    if len(args) == 1:
        if isinstance(args[0],(tuple,list)):
            args = args[0]
        elif isinstance(args[0],str) and len(args[0]) > 1:
            args = args[0]
    if isinstance(args[0], str) and typ is GLubyte:
        return (typ * len(args))(*[ord(c) for c in args])
    else:
        return (typ * len(args))(*args)


def setup_light():

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

    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_LIGHT1)

color_sky = (0.5, 0.69, 1.0, 1)

platform = pyglet.window.get_platform()
display = platform.get_default_display()
screen = display.get_default_screen()
config = screen.get_best_config()
context = config.create_context(None)
#win_cfg = {'config': config, 'width': 1024, 'height': 768, 'visible': True, 'fullscreen': False, 'resizable': False}
win_cfg = {'config': config, 'width': 1920, 'height': 1080, 'visible': True, 'fullscreen': True, 'resizable': False}
window = pyglet.window.Window(context=context, **win_cfg)
glClearColor(*color_sky)
window.clear()
window.set_exclusive_mouse(True)
glMatrixMode(GL_PROJECTION | GL_MODELVIEW)
glLoadIdentity()
glEnable(GL_DEPTH_TEST)

gluPerspective(70.0, window.width / window.height, 0.1, 100.0)
camera = Camera()
world = space.World()
world.set_frustrum()
world.gen_space((0, 0, 0))

setup_light()

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)

@window.event
def on_draw():
    glMatrixMode(GL_PROJECTION |GL_MODELVIEW)
    glLoadIdentity()
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    gluPerspective(70.0, window.width / window.height, 0.1, 100.0)
    gluLookAt(*camera.LookSet)
    world.batch.draw()


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


pyglet.clock.schedule(camera.stream)
pyglet.app.run()
