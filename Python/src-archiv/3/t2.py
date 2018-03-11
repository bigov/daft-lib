# -*- coding:utf-8 -*-

import pyglet
pyglet.options['debug_gl'] = False
from pyglet.gl import *

platform = pyglet.window.get_platform()
display = platform.get_default_display()
screen = display.get_default_screen()
config = screen.get_best_config()
context = config.create_context(None)
win_cfg = {'config':config, 'width':600, 'height':400,
    'visible':True, 'resizable':True}
window = pyglet.window.Window(context=context, **win_cfg)
window.clear()

# Фоновый цвет - голоубой
glClearColor(0.5, 0.69, 1.0, 1)

labels = pyglet.text.Label('', font_name='Verdana', font_size=22,
    color=(60, 60, 60, 255), x=0, y=0, anchor_x='left', anchor_y='center')

#glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
#glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)

import space
world = space.World()

@window.event
def on_draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_PROJECTION | GL_MODELVIEW)
    glLoadIdentity()
    gluPerspective( 45, window.width/window.height, 0.1, 100.0 )
    glTranslatef(-0.5, -0.5, -3.5)
    glRotatef(15, 1, 0, 0)
    world.draw()


pyglet.app.run()
