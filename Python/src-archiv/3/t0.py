# -*- coding:utf-8 -*-
'''   Изучаем возможности pyglet
'''

import pyglet
#from pyglet.gl.glx import Window
''' Отключение проверки ошибок для увеличения производительности
 Установка этого параметра после вызова "pyglet.gl import"
 работать не будет
'''
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

#Set the color of the sky
glClearColor(0.5, 0.69, 1.0, 1)
center_x = window.width//2
center_y = window.height//2
font_size=22

label = pyglet.text.Label('Hello, WORLD!',
    font_name='Verdana',
    font_size=font_size,
    color=(60, 60, 60, 255),
    x=center_x, y=center_y,
    anchor_x='center', anchor_y='center')

fname = 'pennant.png'
from pyglet.image.codecs.png import PNGImageDecoder
img_pennant = pyglet.image.load(fname, decoder=PNGImageDecoder())

orto_cube = [
    100,100,100, 200,100,100, 200,200,100, 100,200,100,
100,100,200, 200,100,200, 200,200,200, 100,200,200,
]

def quard_draw(width, height):
    h = font_size
    c_x = int(width//2)
    c_y = int(height//2)
    my_quad = [
        c_x - 120, c_y - h,
        c_x + 120, c_y - h,
        c_x + 120, c_y + h,
        c_x - 120, c_y + h,
    ]
    h = h + 1
    my_quad_l = [
        c_x - 121, c_y - h,
        c_x + 121, c_y - h,
        c_x + 121, c_y + h-1,
    ]

    pyglet.graphics.draw(4, GL_QUADS,
        ('v2i', my_quad), 
        ('c3f', (0.6,0.6,0.9, 0.6,0.6,0.9, 1,1,1, 1,1,1))
    )

    pyglet.graphics.draw(3, GL_LINE_STRIP,
        ('v2i', my_quad_l),
        ('c3f', (0.4,0.4,0.4, 0.4,0.4,0.4, 0.8,0.8,0.8))
    )

@window.event
def on_draw():
    window.clear()
    #quard_draw(window.width, window.height)
    #label.draw()
    #img_pennant.blit(4, window.height - img_pennant.height - 4, 0)

    #glViewport(0, 0, window.width, window.height)
    glMatrixMode(GL_PROJECTION | GL_MODELVIEW)
    glLoadIdentity()
    gluPerspective( 45, window.width/window.height, 0.1, 100.0 )
    #glMatrixMode(GL_MODELVIEW)
    #glLoadIdentity()
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST)

    glTranslatef(-1.5,0.0,-8.0)
    glBegin(GL_TRIANGLES)
    glVertex3f( 0.0, 1.0, 0.0)
    glVertex3f(-1.0,-1.0, 0.0)
    glVertex3f( 1.0,-1.0, 0.0)
    glEnd()

    glTranslatef(3.0, 0.0, 0.0)
    glBegin(GL_QUADS)
    glVertex3f(-1.0, 1.0, 0.0)
    glVertex3f( 1.0, 1.0, -1.0)
    glVertex3f( 1.0,-1.0, -1.0)
    glVertex3f(-1.0,-1.0, 0.0)
    glEnd()

@window.event
def on_resize(width, height):
    ''' Очевидно, что этот метод автоматически (через event) вызывает
    метод on_draw(), что заметно по тому, как перерисовывается объект, если
    его позиция не вычисляется в момент прорисовки, а задана заранее. 
    Например, объект прямоугольник при вызове пересчитывает координаты,
    а текстовая метка имеет статические координаты. Если изменение по Х
    закомментировать, то при изменении размера окна вширину (по оси X) она
    будет смещаться.
    '''
    label.x = width//2
    label.y = height//2

pyglet.app.run()
