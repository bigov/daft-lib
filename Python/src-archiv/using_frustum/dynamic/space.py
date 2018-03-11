#-*- coding:utf-8 -*-

import random
import pyglet
from pyglet.image.codecs.png import PNGImageDecoder
from pyglet.gl import *
import types
from math import *

class World(object):
    ''' Генератор пространства
    '''
    #нормали
    n_r = (-1.0,  0.0,  0.0)    # право
    n_l = ( 1.0,  0.0,  0.0)    # лево
    n_d = ( 0.0, -1.0,  0.0)    # низ
    n_t = ( 0.0,  1.0,  0.0)    # верх
    n_b = ( 0.0,  0.0, -1.0)    # зад
    n_f = ( 0.0,  0.0,  1.0)    # перед

    cube_normals = (n_r * 4, n_l * 4, n_d * 4, n_t * 4, n_b * 4, n_f * 4)

    #нормали куба: r + l + d + t + b + f
    n_24 = (n_r * 4 + n_l * 4 + n_d * 4 + n_t * 4 + n_b * 4 + n_f * 4)

    # Пирамида видимости
    frustum = None

    # Множество 3D координат ячеек пространства в виде координаты одной
    # центральной точки на каждую ячейку
    space_cells = set()

    def __init__(self):

        # не освещать внутренние поверхности объектов
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE)

        self.batch = pyglet.graphics.Batch()

        # Загрузить изображение
        fname = 'pics/txtr.png'
        img =  pyglet.image.load(fname, decoder=PNGImageDecoder())
        self.TexGroup = pyglet.graphics.TextureGroup(img.get_texture())

    def gen_space(self, location, azim, zenit):
        '''TO-DO: Начальное заполнение пространства при первом запуске. В
        дальнейшем сгенерированную область надо сохранить вместе с положением
        камеры в файл(базу данных) и при запуске загружать.

        Направление взляда от камеры:
            zenit - зенит (от 0 до 180 град.) 0 - pi
            azim - азимут (от 0 до 360 град.) 0 - 2*pi
        '''
        texture = self.tex_coords((3,3), (3,3), (3,3), 1/2)
        space = self.square_3d(location, 100)

        h = 0.5     # высота элементов
        s = 1.0     # длина стороны элементов
        q = []      # массив точек координат вершин граней
        t = []      # координаты текстур
        n = []      # нормали к граням

        # Не отображаем грани, которых не видно ("сзади") за кубом
        draw_r = draw_l = draw_d = draw_t = draw_b = draw_f = True
        
        # грубые условия для отображения граней
        draw_l = (pi+ pi/2) > azim > pi/2
        draw_f = azim > pi/2
        draw_d = zenit < pi/2
        draw_t = zenit > pi/2
        #draw_r = draw_l = draw_d = draw_t = draw_b = draw_f = True

        # Для каждой ячейки рисуем грань только в сторону пустоты
        for point in space:
            (x, y, z) = point
            y0 = (y - 0.5) * h
            y1 = (y + 0.5) * h
            x0 = (x - 0.50) * s
            x1 = (x + 0.50) * s
            z0 = (z - 0.50) * s
            z1 = (z + 0.50) * s

            # right
            if (not (x-1,y,z) in space) and draw_r:
                q.extend((x0, y0, z0, x0, y0, z1, x0, y1, z1, x0, y1, z0))
                t.extend(texture[0])
                n.extend((-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0))
            # left
            if (not (x+1,y,z) in space) and draw_l:
                q.extend((x1, y0, z1, x1, y0, z0, x1, y1, z0, x1, y1, z1))
                t.extend(texture[1])
                n.extend((1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0))
            # down
            if (not (x,y-1,z) in space) and draw_d:
                q.extend((x0, y0, z0, x1, y0, z0, x1, y0, z1, x0, y0, z1))
                t.extend(texture[2])
                n.extend((0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0))
            # top
            if (not (x,y+1,z) in space) and draw_t:
                q.extend((x0, y1, z1, x1, y1, z1, x1, y1, z0, x0, y1, z0))
                t.extend(texture[3])
                n.extend((0.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0))
            # back
            if (not (x,y,z-1) in space) and draw_b:
                q.extend((x1, y0, z0, x0, y0, z0, x0, y1, z0, x1, y1, z0))
                t.extend(texture[4])
                n.extend((0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0))
            # face
            if (not (x,y,z+1) in space) and draw_f:
                q.extend((x0, y0, z1, x1, y0, z1, x1, y1, z1, x0, y1, z1))
                t.extend(texture[5])
                n.extend((0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0))

        # Все координаты отображаемых граней отдаем в OpenGL
        self.batch.add(int(len(q)/3), GL_QUADS, self.TexGroup,
            ('v3f', q), ('t2f', t), ('n3f', n))
        del(q,t,n)

    def square_3d(self, center, size):

        ''' генерирует массив точек в форме горизонтального квадрата
            с длиной стороны "size + 1", центром в точке "center" и
            co случайными изменения по высоте точки
        '''

        # Если массив ячеек еще пустой, то следует сгенерировать новый 
        if not self.space_cells:
            x, y, z = center
            half = int(size / 2)

            x0 = x - half
            x1 = x + half
            z0 = z - half
            z1 = z + half

            for x in range(x0, x1):
                for z in range(z0, z1):
                    self.space_cells.add((x, y+(random.randrange(2)-1), z))
            del(x,x0,x1,z,z0,z1,half)

        square = set()
        self.set_frustrum()
        for cell in self.space_cells:
            x, y, z = cell
            if self.PointInFrustum(x, y, z):
                square.add(cell)

        return square

    def gen_plate(self, x, y, z):
        ''' Генератор координат параллелограммов
        '''
        s = 1.0     # масштаб по горизонтали
        h = 0.5     # масштаб по вертикали

        y0 = (y - 0.5) * h
        y1 = (y + 0.5) * h
        x0 = (x - 0.50) * s
        x1 = (x + 0.50) * s
        z0 = (z - 0.50) * s
        z1 = (z + 0.50) * s

        # верх (Top)
        t = (x0, y1, z1, x1, y1, z1, x1, y1, z0, x0, y1, z0)
        # (Down)
        d = (x0, y0, z0, x1, y0, z0, x1, y0, z1, x0, y0, z1)
        # (Face)
        f = (x0, y0, z1, x1, y0, z1, x1, y1, z1, x0, y1, z1)
        # (Right)
        r = (x0, y0, z0, x0, y0, z1, x0, y1, z1, x0, y1, z0)
        # (Back)
        b = (x1, y0, z0, x0, y0, z0, x0, y1, z0, x1, y1, z0)
        # (Left)
        l = (x1, y0, z1, x1, y0, z0, x1, y1, z0, x1, y1, z1)

        return (r, l, d, t, b, f)

    def tex_coord(self, x, y, n=4):
        """ Генерирует координаты прямоугольной области текстуры, загруженной
        из файла текстур. Изображения текстур представляют собой квадраты
        с равным соотношением сторон, расположенные в форме заполненного
        квадрата.
        
        В функцию в качестве праметров выбора передаются три целых числа:
            n - количество квадратов текстур вдоль стороны файла текстур,
            x - номер выбранного квадрата текстуры по горизонтали,
            y - номер выбранного квадрата по вертикали,

        Начало отсчета от левого/нижнего угла, от нуля: первая (x=0.0,y=0.0)

        Результат представляет собой координаты точек квадратной области с
        выбранной текстурой в относительных значениях от 0.0 до 1.0. Таким
        образом правый-верхний угол файла имеет координаты (1.0, 1.0)

        """
        m = 1.0 / n
        x0 = x * m
        y0 = y * m
        x1 = x0 + m
        y1 = y0 + m
        return (x0, y0, x1, y0, x1, y1, x0, y1)

    def tex_coords(self, top, down, sid, sid_part):
        """ Генерирует точки координат текстуры для параллелограмма, по
        координатам квадратов полей в текстурной карте с раздельным
        указанием текстур для верха, низа и боковых сторон.
        
        Возвращает список из 48 точек координат - 24 двухмерных координаты.
        
        sid_part - отделяемая часть по высоте (высота стороны параллелепипеда) 

        """
        t = self.tex_coord(*top)
        d = self.tex_coord(*down)
        (x0, y0, x1, y0, x1, y1, x0, y1) = self.tex_coord(*sid)
        s = (x0, y0, x1, y0, x1, y1 * sid_part, x0, y1 * sid_part)
        # r, l, d, t, b, f
        coords = [s[:], s[:], d[:], t[:], s[:], s[:]]
        del (t, d, s, x0, y0, x1, y1)
        return coords

    def PointInFrustum(self, x, y, z):
        ''' Если объект в пирамиде видимости, то ворзвращается расстояние
            от объекта до наблюдателя, если нет - 0
        '''
        radius = 3
        for p in range(6):
            d = (self.frustum[p][0] * x + self.frustum[p][1] * y +
                self.frustum[p][2] * z + self.frustum[p][3])
            if( d <= -radius ):
                return 0
        return d + radius

    def set_frustrum(self):
        ''' Расчет матрицы пирамиды видимости (self.frustum)

            Использована статья "Урок X2. Отсечение по пирамиде
            видимости в OpenGL" http://pmg.org.ru/nehe/nehex2.htm
        '''

        proj = (GLfloat * 16)(0.0)
        modl = (GLfloat * 16)(0.0)
        clip = (GLfloat * 16)(0.0)

        # текущая матрица PROJECTION
        glGetFloatv(GL_PROJECTION_MATRIX, proj)

        # текущая матрица MODELVIEW
        glGetFloatv(GL_MODELVIEW_MATRIX, modl)

        # Комбинируем матрицы(перемножаем)
        clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12]
        clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13]
        clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14]
        clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15]
        clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12]
        clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13]
        clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14]
        clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15]
        clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12]
        clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13]
        clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14]
        clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15]
        clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12]
        clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13]
        clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14]
        clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15]
        del(modl,proj)

        f0 = [0,0,0,0,0]
        f1 = [0,0,0,0,0]
        f2 = [0,0,0,0,0]
        f3 = [0,0,0,0,0]
        f4 = [0,0,0,0,0]
        f5 = [0,0,0,0,0]

        # ПРАВО
        f0[0] = clip[ 3] - clip[ 0]
        f0[1] = clip[ 7] - clip[ 4]
        f0[2] = clip[11] - clip[ 8]
        f0[3] = clip[15] - clip[12]
        #Приводим уравнение плоскости к нормальному виду
        t = sqrt( f0[0] * f0[0] + f0[1] * f0[1] + f0[2] * f0[2])
        f0[0] /= t
        f0[1] /= t
        f0[2] /= t
        f0[3] /= t

        # ЛЕВО
        f1[0] = clip[ 3] + clip[ 0]
        f1[1] = clip[ 7] + clip[ 4]
        f1[2] = clip[11] + clip[ 8]
        f1[3] = clip[15] + clip[12]
        t = sqrt( f1[0] * f1[0] + f1[1] * f1[1] + f1[2] * f1[2])
        f1[0] /= t
        f1[1] /= t
        f1[2] /= t
        f1[3] /= t

        # НИЗ
        f2[0] = clip[ 3] + clip[ 1]
        f2[1] = clip[ 7] + clip[ 5]
        f2[2] = clip[11] + clip[ 9]
        f2[3] = clip[15] + clip[13]
        t = sqrt( f2[0] * f2[0] + f2[1] * f2[1] + f2[2] * f2[2])
        f2[0] /= t
        f2[1] /= t
        f2[2] /= t
        f2[3] /= t

        # ВЕРХ
        f3[0] = clip[ 3] - clip[ 1]
        f3[1] = clip[ 7] - clip[ 5]
        f3[2] = clip[11] - clip[ 9]
        f3[3] = clip[15] - clip[13]
        t = sqrt( f3[0] * f3[0] + f3[1] * f3[1] + f3[2] * f3[2])
        f3[0] /= t
        f3[1] /= t
        f3[2] /= t
        f3[3] /= t

        # Задняя (дальняя от наблюдателя) плоскость
        f4[0] = clip[ 3] - clip[ 2]
        f4[1] = clip[ 7] - clip[ 6]
        f4[2] = clip[11] - clip[10]
        f4[3] = clip[15] - clip[14]
        t = sqrt( f4[0] * f4[0] + f4[1] * f4[1] + f4[2] * f4[2])
        f4[0] /= t
        f4[1] /= t
        f4[2] /= t
        f4[3] /= t

        # Передняя плоскость
        f5[0] = clip[ 3] + clip[ 2]
        f5[1] = clip[ 7] + clip[ 6]
        f5[2] = clip[11] + clip[10]
        f5[3] = clip[15] + clip[14]
        t = sqrt( f5[0] * f5[0] + f5[1] * f5[1] + f5[2] * f5[2])
        f5[0] /= t
        f5[1] /= t
        f5[2] /= t
        f5[3] /= t

        self.frustum = (tuple(f0),tuple(f1),tuple(f2),tuple(f3),tuple(f4),tuple(f5))
        del(f0,f1,f2,f3,f4,f5,clip)
        
        #print(self.frustum)
