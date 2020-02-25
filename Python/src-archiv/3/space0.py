# -*- coding:utf-8 -*-

import pyglet

class World(object):
    ''' Генератор пространства
    '''

    def __init__(self):

        self.batch = pyglet.graphics.Batch()
        texture = Texture('txtr.png')
        tile = ('v3f/static', self.tile_points(-1, 0, 0))
        self.batch_add_quad(texture, tile)

        tile = ('v3f/static', self.tile_points(0, 0, 0))
        self.batch_add_quad(texture, tile)

        tile = ('v3f/static', self.tile_points(1, 0, 0))
        self.batch_add_quad(texture, tile)

        tile = ('v3f/static', self.tile_points(-1, 0, -1))
        self.batch_add_quad(texture, tile)

        tile = ('v3f/static', self.tile_points(0, 0, -1))
        self.batch_add_quad(texture, tile)

        tile = ('v3f/static', self.tile_points(1, 0, -1))
        self.batch_add_quad(texture, tile)

        tile = ('v3f/static', self.tile_points(-1, 0, -2))
        self.batch_add_quad(texture, tile)

        tile = ('v3f/static', self.tile_points(0, 0, -2))
        self.batch_add_quad(texture, tile)

        tile = ('v3f/static', self.tile_points(1, 0, -2))
        self.batch_add_quad(texture, tile)


    def batch_add_quad(self, texture, points):

        mode = pyglet.gl.GL_QUADS
        self.batch.add( 4, mode, texture.group, points, texture.points )


    def draw(self):
        self.batch.draw()


    def tile_points(self, x, y, z):

        return [
            x - 0.50, y, z - 0.50,
            x + 0.50, y, z - 0.50,
            x + 0.50, y, z + 0.50,
            x - 0.50, y, z + 0.50 ]

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



