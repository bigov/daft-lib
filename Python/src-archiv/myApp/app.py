#!/usr/bin/env python
# -*- coding:utf-8 -*-

import tricks
import rig

import time
from multiprocessing import Process, Manager
from pyglet.gl import *
from pyglet.window import key
from pyglet import clock

from tricks import *
from os.path import sep
from math import sqrt
from copy import deepcopy

import space
from layout import Camera


def setup_light():
    """ Параметры источников света

        ambient - фоновый (всенаправленный)
        difuuze - диффузный направленный
        specular - зеркальный
    """
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (GLfloat * 4)(0.3, 0.1, 0.1, 1.0))
    # не освещать внутренние поверхности объектов
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE)

    # основной - желтоватый
    glLightfv(GL_LIGHT0, GL_DIFFUSE, (GLfloat * 4)(1.45, 1.45, 1.30, 1.00))
    glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat * 4)(0.30, 0.30, 0.30, 1.00))
    glLightfv(GL_LIGHT0, GL_SPECULAR, (GLfloat * 4)(0.30, 0.30, 0.30, 1.00))
    # задняя подсветка - серая
    glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat * 4)(1.0, 1.0, 1.0, 1.0))
    glLightfv(GL_LIGHT1, GL_AMBIENT, (GLfloat * 4)(0.0, 0.0, 0.0, 1.0))
    glLightfv(GL_LIGHT1, GL_SPECULAR, (GLfloat * 4)(0.0, 0.0, 0.0, 1.0))

    glEnable(GL_LIGHT0)
    glEnable(GL_LIGHT1)


def set_light():
    """ Позиция источников света
    """
    glLightfv(GL_LIGHT0, GL_POSITION, glType(GLfloat, -6.0, 6.40, -5.5, 0.0))
    glLightfv(GL_LIGHT1, GL_POSITION, glType(GLfloat, 5.0, -2.5, 6.0, 0.0))


def set_fog():
    glEnable(GL_FOG)  # активировать режим тумана
    glFogi(GL_FOG_MODE, GL_LINEAR)  # закон смешения тумана
    glFogf(GL_FOG_START, 60)  # начало тумана
    glFogf(GL_FOG_END, 100)  # конец тумана
    # цвет дымки
    glFogfv(GL_FOG_COLOR, (GLfloat * 4)(0.5, 0.7, 1.0, 1))
    glFogf(GL_FOG_DENSITY, 0.7)  # плотность тумана
    glHint(GL_FOG_HINT, GL_DONT_CARE)  # GL_DONT_CARE | GL_NICEST | GL_FASTEST


def set_2d():
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
    glEnable(GL_LIGHTING)
    glEnable(GL_DEPTH_TEST)
    glDepthFunc(GL_LESS)
    glEnable(GL_CULL_FACE)
    glFrontFace(GL_CCW)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_PROJECTION | GL_MODELVIEW)
    glLoadIdentity()
    width, height = window.get_size()
    gluPerspective(70.0, width / height, 0.1, 100.0)
    set_light()


def draw_focused_unit(point):
    """ Подсвечивает рамкой блок, на который направлен взгляд(курсор),
    только если наблюдатель не находится внутри существующего ("твердого") блока.
    :param point: tuple
    :return: void
    """
    x, y, z = camera.myPos
    if (round(x), round(y), round(z)) not in rig.active_units:
        glDisable(GL_LIGHTING)
        pyglet.gl.glColor4f(0.9, 0.9, 1.0, 0.1)
        pyglet.graphics.draw(24, GL_QUADS, ('v3f/static', tricks.get_frame_vertices(point)))
        glEnable(GL_LIGHTING)


def draw_2d_content():

    az = str('%.3f' % round(camera.azim, 3))
    ze = str('%.3f' % round(camera.zenit, 3))
    to = str(camera.look_to())
    text = "azim: %s, zenit: %s, look to: %s" % (az, ze, to)

    set_2d()
    label = pyglet.text.Label(text, font_name='DejaVu Sans Mono',
                              font_size=10, color=(45, 45, 245, 255), x=20, y=window.height - 18,
                              anchor_x='left', anchor_y='top')

    info_quad(window.height, 370, 36)
    show_sight(int(window.width/2), int(window.height/2))
    label.draw()


def app_init():
    pyglet.font.add_file("pics%sttf%sDejaVuSansMono.ttf" % (sep, sep))
    pyglet.font.load('DejaVu Sans Mono')
    glPolygonMode(GL_FRONT, GL_FILL)
    glEnable(GL_BLEND)  # включить поддержку прозрачности

    # Управление массивом элеменов 3D пространства
    rig.space_batch = pyglet.graphics.Batch()


def calc_remove(units_removing, points_checking):
    """ Обновление состава активных элементов отображения трехмерного пространства:
     - элементы/блоки,расстояние до которых от наблюдателя больше границы видимости - удаляются,
     (- при сдвиге границы видимости новые видимые блоки должны добавляться)

    :units_removing: list
    :points_checking: list
    :return: void
    """
    far_max = 50.0

    """
    while True:
        if points_checking:
            # сamera.location()
            x1, y1, z1 = points_checking.pop(-1)

            while points_checking:
                x2, y2, z2 = points_checking.pop()
                # контролируем дистанцию только по горизотали
                distance = sqrt((x2-x1)**2 +(z2-z1)**2)
                if distance > far_max:
                    units_removing.append((x2, y2, z2))
    """

if __name__ == '__main__':
    window = window_open()
    camera = Camera()

    # import time
    # start_run = time.time()
    # print("init time: %f" % (time.time() - start_run))

    app_init()
    world = space.World()

    units_init = deepcopy(rig.active_units)

    setup_light()
    set_fog()

    # Динамическое изменение элементов активного пространства
    from multiprocessing import Manager
    units_removing = Manager().list()
    points_checking = Manager().list()
    p = Process(target=calc_remove, args=(units_removing, points_checking))
    p.start()

    # текущее значение ftp можно получить через = fps.clock.get_fps()
    fps = clock.ClockDisplay(format='%(fps).2f', color=(1.0, 1.0, 1.0, 0.8))

    @window.event
    def on_key_press(symbol, modifiers):

        key_pressed_point = camera.location()
        if symbol == key.ESCAPE:
            window.set_exclusive_mouse(False)
        else:
            camera.key_press(symbol, modifiers)

        # Если нет активной очереди на удаление, то добавим новую
        #if not units_removing:
        #    points_checking.extend(rig.active_units.keys())
        #    points_checking.append(key_pressed_point)

    @window.event
    def on_draw():
        gluLookAt(*camera.LookSet)
        set_3d()
        world.draw()
        p = camera.look_to()
        if p:
            draw_focused_unit(p)
        draw_2d_content()
        fps.draw()

        # Если имеются элементы загрузки
        if units_init:
            l = min(len(units_init), 500)
            for x in range(l):
                p, texture_id = units_init.popitem()
                if type(texture_id) == int:
                    rig.active_units[p] = space.Unit(p, texture_id)

        """
        # Если имеются элементы, вышедшие за границу видимости, то их следует
        # удалить из рендеринга
        if units_removing:
            # Чтобы не тормозить движение камеры - удаляем частями по 50 элементов
            # при каждой перерисовке экрана
            l = min(len(units_removing), 50)
            for x in range(l):
                p = units_removing.pop()
                u = rig.active_units.pop(p)
                u.delete()
        """
    @window.event
    def on_mouse_motion(x, y, dx, dy):
        camera.turn_look(x, y, dx, dy)

    @window.event
    def on_mouse_press(x, y, button, modifiers):
        look_to = camera.look_to()
        if look_to and button == pyglet.window.mouse.RIGHT:
            e = rig.active_units.pop(look_to)
            e.delete()

    @window.event
    def on_key_release(symbol, modifiers):
        camera.key_release(symbol, modifiers)


    pyglet.clock.schedule(camera.stream)
    pyglet.app.run()
    p.terminate()
    p.join()
