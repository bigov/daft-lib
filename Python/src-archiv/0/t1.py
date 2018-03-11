# -*- coding:utf-8 -*-

import pyglet
from pyglet.gl import *

platform = pyglet.window.get_platform()
display = platform.get_default_display()
screen = display.get_default_screen()
config = screen.get_best_config()
context = config.create_context(None)
win_cfg = {'config':config, 'width':600, 'height':400,
    'visible':True, 'resizable':True}

window = pyglet.window.Window(context=context, **win_cfg)

def cube_vertices(x, y, z, n):
    return [
        x-n,y+n,z-n, x-n,y+n,z+n, x+n,y+n,z+n, x+n,y+n,z-n,  # top
        x-n,y-n,z-n, x+n,y-n,z-n, x+n,y-n,z+n, x-n,y-n,z+n,  # bottom
        x-n,y-n,z-n, x-n,y-n,z+n, x-n,y+n,z+n, x-n,y+n,z-n,  # left
        x+n,y-n,z+n, x+n,y-n,z-n, x+n,y+n,z-n, x+n,y+n,z+n,  # right
        x-n,y-n,z+n, x+n,y-n,z+n, x+n,y+n,z+n, x-n,y+n,z+n,  # front
        x+n,y-n,z-n, x-n,y-n,z-n, x-n,y+n,z-n, x+n,y+n,z-n,  # back
    ]  

def content_draw():
    # light blue color
    pyglet.gl.glClearColor(0.5, 0.69, 1.0, 1)
    window.clear()
    vertex_data = cube_vertices(1,1,-5,1)
    pyglet.graphics.draw(24, GL_QUADS, ('v3i', vertex_data))

@window.event
def on_draw():
    content_draw()

pyglet.app.run()
