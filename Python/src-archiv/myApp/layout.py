# -*- coding:utf-8 -*-

import math
from math import cos, sin
from pyglet.window import key
from pyglet.gl import *
import rig


class Camera(object):

    # Чувствительность мышки
    sense_v = 0.001
    sense_h = 0.002
    on_keys = []
    # Скорость подъема/спуска в режиме полета
    fly_step = 0.04
    # координаты игрока
    myPos = (0.0, 2.0, 0.0)
    #координаты точки взгяда
    myLook = (0.0, 2.0, -2.0)
    # направление "вверх"
    upDir = (0.0, 1.0, 0.0)

    # DEBUG: настройка света
    # AMBIENT = 0.0
    # DIFFUSE = 0.0

    def __init__(self):

        self.LookSet = self.myPos + self.myLook + self.upDir

        """ TODO: Начально положение взгляда игрока должно загружаться
                из файла сохранения предыдущего состояния
        """
        gluLookAt(*self.LookSet)

        # Направление взляда игрока
        # зенит (от 0 до 180 град.)
        self.zenit = math.pi/2.0
        # азимут (от 0 до 360 град.)
        self.azim = math.pi + self.zenit

    def location(self):
        """ возвращает текущие координаты положения камеры
        """
        return self.myPos

    def get_sight_vector(self):
        """ Returns the vector of the direction the player is looking.
        """
        m = math.sin(self.zenit)
        dx = math.cos(self.azim) * m
        dy = math.cos(self.zenit)
        dz = math.sin(self.azim) * m
        return dx, dy, dz

    def look_to(self):
        """ Возвращает координаты точки, на которую направлен взгляд в пределах distance
        :return: tuple
        """
        distance = 8    # дистанция поиска
        step = 0.01     # шаг (точность)

        x, y, z = self.myPos
        dx, dy, dz = self.get_sight_vector()
        dx *= step
        dy *= step
        dz *= step

        k = p = (round(x), round(y), round(z))
        for _ in range(distance):
            while p == k:
                x += dx
                y += dy
                z += dz
                p = (round(x), round(y), round(z))
            if p in rig.active_units:
                return p
            else:
                k = p

        return None

    def turn_look(self, x, y, dx, dy):

        self.zenit = self.zenit - dy * self.sense_v
        self.azim = self.azim + dx * self.sense_h

        # Dp = 2 * "пи" = 360 град 
        Dp = 2.0 * math.pi
        if (self.azim > Dp): self.azim = self.azim - Dp
        if (self.azim < 0): self.azim = Dp - self.azim
        self.zenit = max(0.000001, min(self.zenit, math.pi - 0.000001))

        r = 2.0
        lx = r * sin(self.zenit) * cos(self.azim)
        lz = r * sin(self.zenit) * sin(self.azim)
        ly = r * cos(self.zenit)

        x, y, z = self.myPos

        self.myLook = (x + lx, y + ly, z + lz)
        self.LookSet = self.myPos + self.myLook + self.upDir

    def key_press(self, symbol, modifiers):

        self.on_keys.append(symbol)
        self.stream(1)

    def stream(self, dt):
        
        if len(self.on_keys) == 0: return
        
        step = 0.1
        side = math.pi/2.0
        
        fb_x = fb_z = rl_x = rl_z = d_y = 0

        if key.W in self.on_keys:
            fb_x = step * cos( self.azim )
            fb_z = step * sin( self.azim )
        elif key.S in self.on_keys:
            fb_x = -1.0 * step * cos( self.azim )
            fb_z = -1.0 * step * sin( self.azim )

        if key.A in self.on_keys:
            rl_x = step * cos( self.azim - side)
            rl_z = step * sin( self.azim - side)
        elif key.D in self.on_keys:
            rl_x = -1.0 * step * cos( self.azim - side)
            rl_z = -1.0 * step * sin( self.azim - side)

        if key.SPACE in self.on_keys:
            d_y = self.fly_step
        elif key.LSHIFT in self.on_keys:
            d_y = - self.fly_step

        x, y, z = self.myPos
        self.myPos = (x + rl_x + fb_x, y + d_y, z + rl_z + fb_z)

        x, y, z = self.myLook
        self.myLook = (x + rl_x + fb_x, y + d_y, z + rl_z + fb_z)

        self.LookSet = self.myPos + self.myLook + self.upDir

    def key_release(self, symbol, modifiers):
        self.on_keys.remove(symbol)


    