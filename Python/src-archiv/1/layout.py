# -*- coding:utf-8 -*-

import math
from math import cos, sin
from pyglet.window import key
from pyglet.gl import *
from _ast import Str

class Camera(object):

    #Translate = (0, 0, 0)
    #Rotate = (0, 0, 0, 0)
    # Чувствительность мышки
    sense_v = 0.001
    sense_h = 0.001
    on_keys = []
    # координаты игрока
    myPos = [0.0, 2.0, 0.0]
    #координаты точки взгяда
    myLook = [2.0, 2.0, 0.0]
    # направление "вверх"
    upDir = [0.0, 1.0, 0.0]

    # азимут (от 0 до 360 град.)
    azim = 0.0

    # DEBUG: настройка света
    # AMBIENT = 0.0
    # DIFFUSE = 0.0

    def __init__(self):

        self.LookSet = self.myPos + self.myLook + self.upDir

        '''TODO: Начально положение взгляда игрока должно загружаться
                из файла сохранения предыдущего состояния
        '''
        gluLookAt(*self.LookSet)

        # Направление взляда игрока
        # зенит (от 0 до 180 град.)
        self.zenit = math.pi/2.0
        self.azim = 0.0

    def location(self):
        ''' возвращает текущие координаты положения камеры
        '''
        return self.myPos

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

        self.myLook = [x + lx, y + ly, z + lz]
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
            d_y = step
        elif key.LSHIFT in self.on_keys:
            d_y = - step

        '''
        if key.O in self.on_keys:
            self.AMBIENT += 0.01
        elif key.L in self.on_keys:
            self.AMBIENT -= 0.01
            if self.AMBIENT < 0:
                self.AMBIENT = 0
        elif key.I in self.on_keys:
            self.DIFFUSE += 0.01
        elif key.K in self.on_keys:
            self.DIFFUSE -= 0.01
            if self.DIFFUSE < 0:
                self.DIFFUSE = 0

        a = self.AMBIENT
        d = self.DIFFUSE
        print( 'AMBIENT: ' + str(a) + '; DIFFUSE: ' + str(d))
         
        #glLightfv(GL_LIGHT1, GL_AMBIENT, (GLfloat * 4)(a, a, a, 1.00))
        glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat * 4)(d, d, d, 1.00))
        '''

        x, y, z = self.myPos
        self.myPos = [x + rl_x + fb_x, y + d_y, z + rl_z + fb_z]

        x, y, z = self.myLook
        self.myLook = [x + rl_x + fb_x, y + d_y, z + rl_z + fb_z]

        self.LookSet = self.myPos + self.myLook + self.upDir

    def key_release(self, symbol, modifiers):
        self.on_keys.remove(symbol)


    