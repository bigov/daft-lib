#!/usr/bin/env python
# -*- coding:utf-8 -*-

import pyglet
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

    #glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE)
    # Ночной свет (без теней)
    #glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (GLfloat * 4)(0.3, 0.3, 0.6, 1.0))
    #glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (GLfloat * 4)(0.0, 0.0, 0.0, 1.0))

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

def setup_fog():
    """ Configure the OpenGL fog properties.

    """
    # Enable fog. Fog "blends a fog color with each rasterized pixel fragment's
    # post-texturing color."
    glEnable(GL_FOG)
    # blending factor. GL_LINEAR | GL_EXP
    glFogi(GL_FOG_MODE, GL_LINEAR)
    # Set the fog color.
    glFogfv(GL_FOG_COLOR, (GLfloat * 4)(0.5, 0.69, 1.0, 1.0))
    glFogf(GL_FOG_DENSITY, 1.0)
    # Say we have no preference between rendering speed and quality.
    glHint(GL_FOG_HINT, GL_DONT_CARE)
    
    # How close and far away fog starts and ends. The closer the start and end,
    # the denser the fog in the fog range.
    glFogf(GL_FOG_START, 20.0)
    glFogf(GL_FOG_END, 60.0)

def glType(typ, *args):
    """return ctypes array of GLwhatever for Pyglet's OpenGL interface. (This
    seems to work for all types, but it does almost no type conversion. Just
    think in terms of "C without type casting".)
    typ -> ctype or GL name for ctype; see pyglet.gl.GLenum through GLvoid
    args -> Either vararg, or args[0] as an iterable container
    Examples:
        # Float
        ar = gl_vec(GLfloat, 0.0, 1.0, 0.0)
        ar = gl_vec(GLfloat, [0.0, 1.0, 0.0])
        # Unsigned byte
        ar = gl_vec(GLubyte, 'a','b','c')
        ar = gl_vec(GLubyte, 'abc')
        ar = gl_vec(GLubyte, ['a','b','c'])
        ar = gl_vec(GLubyte, 97, 98, 99)
    """
    if len(args) == 1:
        if isinstance(args[0],(tuple,list)):
            args = args[0]
        elif isinstance(args[0],str) and len(args[0]) > 1:
            args = args[0]
    if isinstance(args[0], str) and typ is GLubyte:
        return (typ * len(args))(*[ord(c) for c in args])
    else:
        return (typ * len(args))(*args)


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
win_cfg = {'config': config, 'width': 1920, 'height': 1080,
    'visible': True, 'fullscreen': True, 'resizable': False}
window = pyglet.window.Window(context=context, **win_cfg)

glClearColor(*cfg.color_0)
window.clear()

labels = pyglet.text.Label('X', font_name='Verdana', font_size=22,
    color=(0, 0, 0, 255), x=10, y=10, anchor_x='left', anchor_y='center')

window.set_exclusive_mouse(True)

glViewport(0,0, window.width, window.height)    #Reset The Current Viewport
glMatrixMode(GL_PROJECTION | GL_MODELVIEW)     #Select The Projection Matrix
glLoadIdentity()                               #Reset The Matrix

glEnable(GL_NORMALIZE)
glEnable(GL_DEPTH_TEST)
#glDepthFunc(GL_ALWAYS) - Какой лучше?
glDepthFunc(GL_LESS)

glEnable(GL_STENCIL_TEST)

camera = Camera()
world = space.World()

#glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE)
#glEnable(GL_MULTISAMPLE_ARB)

# Clear stencil buffer with zero, increment by one whenever anybody
# draws into it. When stencil function is enabled, only write where
# stencil value is zero. This prevents the transparent shadow from drawing
# over itself
#glStencilOp(GL_INCR, GL_INCR, GL_INCR)
#glClearStencil(0)
#glStencilFunc(GL_EQUAL, 0x0, 0x01)

# Cull backs of polygons
#glCullFace(GL_BACK)
#glFrontFace(GL_CCW)
#glEnable(GL_CULL_FACE)


setup_light()
#setup_fog()
'''
the opengl blending faq:
http://www.opengl.org/resources/faq/technical/transparency.htm

glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA) 
'''

@window.event
def on_draw():
    glLoadIdentity()
    #glTranslatef(0.0, 0.0, 0.0)
    #glRotatef(0.0, 0.0, 0.0, 0.0)
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_PROJECTION |GL_MODELVIEW)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)

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


@window.event
def on_resize(width, height):
    pass

@window.event
def on_window_close():
    import pickle
    entry = world.space
    with open('entry.pickle', 'wb') as f:
        pickle.dump(entry, f)
    '''
    Чтение данных:
    import pickle
    with open('entry.pickle', 'rb') as f:
        entry = pickle.load(f)   
    '''    
         

pyglet.clock.schedule(camera.stream)
pyglet.app.run()
