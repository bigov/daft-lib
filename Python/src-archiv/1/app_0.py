#-*- coding:utf-8 -*-

import pyglet
pyglet.options['debug_gl'] = True
from pyglet.gl import *
from pyglet.window import key

import space
import move


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

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)

world = space.World()
window.set_exclusive_mouse(True)

move = move.Set()
from model import Model
db = Model()


@window.event
def on_mouse_motion(x, y, dx, dy):
    move.turn_look(x, y, dx, dy)


@window.event
def on_key_press(symbol, modifiers):
    if (symbol == key.ESCAPE):
        window.set_exclusive_mouse(False)
    else:
        move.key_press(symbol, modifiers)


@window.event
def on_key_release(symbol, modifiers):
    move.key_release(symbol, modifiers)


@window.event
def on_draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_PROJECTION | GL_MODELVIEW)
    glLoadIdentity()
    gluPerspective(64, window.width / window.height, 0.1, 150.0)
    #glTranslatef(*move.Translate)
    #glRotatef(*move.Rotate)
    gluLookAt(*move.LookSet)
    world.draw()


@window.event
def on_resize(width, height):
    pass


def stream(dt):
    move.stream(dt)


pyglet.clock.schedule(stream)
pyglet.app.run()
