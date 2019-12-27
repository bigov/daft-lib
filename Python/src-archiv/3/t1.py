# -*- coding:utf-8 -*-

import pyglet
from pyglet.gl import *

config = pyglet.window.get_platform().get_default_display().get_default_screen().get_best_config()
context = config.create_context(None)
win_cfg = {'config': config, 'width': 700, 'height': 400, 'visible': True, 'resizable': True}
window = pyglet.window.Window(context=context, **win_cfg)

glClearColor(0.5, 0.69, 1.0, 1.0)
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

d = pyglet.image.codecs.png.PNGImageDecoder()
img = pyglet.image.load('txtr.png', decoder=d).get_texture()
TextureGroup = pyglet.graphics.TextureGroup(img)

texture = (0.0, 0.0, 0.25, 0.0, 0.25, 0.25, 0.0, 0.25)
my_pl = (-4, -2.0, -4.0, 4.0, -2.0, -4.0, 4.0, -2.0, -9.0, -4.0, -2.0, -9.0)

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)

batch = pyglet.graphics.Batch()
batch.add(4, GL_QUADS, TextureGroup, ('v3f', my_pl), ('t2f', texture))
glEnable(GL_LIGHTING)
glEnable(GL_LIGHT0)

my_pl = (-4.1, -2.1, -4.1, 4.1, -2.1, -4.1, 4.1, -2.1, -9.1, -4.1, -2.1, -9.1)
#glColor3f(1.0, 0.0, 0.0)
pyglet.graphics.draw(4, GL_LINE_LOOP, ('v3f', my_pl))

@window.event
def on_draw():
    window.clear()
    glMatrixMode(GL_PROJECTION | GL_MODELVIEW)
    glLoadIdentity()
    gluPerspective(45, window.width/window.height, 0.1, 100.0)
    glColor3f(0.6, 0.9, 0.6)
    batch.draw()
    glPolygonMode(GL_FRONT, GL_LINE)
    glDisable(GL_LIGHTING)
    pyglet.gl.glColor4f(1.0, 0.0, 0.0, 1.0)
    pyglet.graphics.draw(4, GL_LINE_LOOP, ('v3f', my_pl))
    glEnable(GL_LIGHTING)
    glPolygonMode(GL_FRONT, GL_FILL)

@window.event
def on_resize(width, height):
    pass

pyglet.app.run()
