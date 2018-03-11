# -*- coding:utf-8 -*-
'''   Изучаем возможности pyglet
'''

import pyglet
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
win_cfg = {'config':config, 'width':600, 'height':400}
window = pyglet.window.Window(**win_cfg)

#Set the color of "clear", i.e. the sky, in rgba.
pyglet.gl.glClearColor(0.5, 0.69, 1.0, 1)
center_x = window.width//2
center_y = window.height//2
font_size=22

msg = 'Hello, World!'
#msg = 'привет, Мир!'
label = pyglet.text.Label(msg,
    font_name='Verdana',
    font_size=font_size,
    color=(60, 60, 60, 255),
    x=center_x, y=center_y,
    anchor_x='center', anchor_y='center')

#img_pennant = pyglet.resource.image('pennant.jpg')
img_pennant = pyglet.image.load('pennant.jpg')

# Координаты 
my_quad = [
    center_x - 120, center_y - font_size,
    center_x + 120, center_y - font_size,
    center_x + 120, center_y + font_size,
    center_x - 120, center_y + font_size,
    ]

@window.event
def on_draw():
    window.clear()
    pyglet.graphics.draw(4, GL_QUADS, 
        ('v2i', my_quad), 
        ('c3f', (0.6,0.6,0.9, 0.6,0.6,0.9, 1,1,1, 1,1,1))
    )
    label.draw()
    img_pennant.blit(4, window.height - img_pennant.height - 4, 0)
pyglet.app.run()
