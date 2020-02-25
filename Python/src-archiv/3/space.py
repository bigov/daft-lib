# -*- coding:utf-8 -*-

import pyglet

class World(object):
    ''' Генератор пространства
    '''

    def __init__(self):

        mode = pyglet.gl.GL_QUADS
        self.batch = pyglet.graphics.Batch()
        texture = Texture('txtr.png')

        points = [
                  0, 0, 0,
                  0, 1, 0,
                  1, 1, 0,
                  1, 0, 0,
                  ]
        points += [0, 1, 0,
                  1, 1, 0,
                  1, 1, 1,
                  0, 1, 1,]



        self.batch.add( 8, mode, texture.group,
                ('v3f/static', points), texture.points )

    def draw(self):
        self.batch.draw()

class Texture(object):
    ''' Формирователь текстур
    '''

    def __init__(self, image_fname):
        
        self.load_image(image_fname)
        region = [0, 0, 64, 64]
        r = self.get_group(region)
        self.group = self.get_group(r)
        self.points = ('t2f/static', self.get_points())

    def get_points(self):
        
        return [ 0.0, 0.0,
                 1.0, 0.0,
                 1.0, 1.0,
                 0.0, 1.0,
                 0.0, 0.0,
                 1.0, 0.0,
                 1.0, 1.0,
                 0.0, 1.0 ]

    def load_image(self, fname):
        ''' Получить файл изображения
        '''
        from pyglet.image.codecs.png import PNGImageDecoder
        self.image = pyglet.image.load(fname, decoder=PNGImageDecoder())

        
    def get_group(self, region):
        ''' Вырезать из файла текстуры указанную область
        '''
        i = self.image
        t = i.get_region(0, 0, 64, 64)
        return pyglet.graphics.TextureGroup(t.get_texture())
