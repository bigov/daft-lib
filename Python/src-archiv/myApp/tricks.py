# -*- coding:utf-8 -*-

import pyglet
import rig


def window_open():
    """ Создание окна приложения
    """
    platform = pyglet.window.get_platform()
    display = platform.get_default_display()
    #screen=pyglet.window.get_platform().get_default_display().get_default_screen()
    screen = display.get_default_screen()

    config = screen.get_best_config()
    context = config.create_context(None)
    #win_cfg = {'config': config, 'width': 1920, 'height': 1080, 'visible': True, 'fullscreen': True, 'resizable': False}
    win_cfg = {'config': config, 'width': 1024, 'height': 768, 'visible': True, 'fullscreen': False, 'resizable': False}
    w = pyglet.window.Window(context=context, **win_cfg)
    w.set_exclusive_mouse(True)
    w.set_location(60, 0)
    return w


def get_frame_vertices(point):
    (x, y, z) = point
    h = rig.height_to_length
    y0 = (y - 0.53) * h
    y1 = (y + 0.53) * h
    x0 = x - 0.53
    x1 = x + 0.53
    z0 = z - 0.53
    z1 = z + 0.53

    return (x0, y0, z0, x0, y0, z1, x0, y1, z1, x0, y1, z0,
            x1, y0, z1, x1, y0, z0, x1, y1, z0, x1, y1, z1,
            x0, y0, z0, x1, y0, z0, x1, y0, z1, x0, y0, z1,
            x0, y1, z1, x1, y1, z1, x1, y1, z0, x0, y1, z0,
            x1, y0, z0, x0, y0, z0, x0, y1, z0, x1, y1, z0,
            x0, y0, z1, x1, y0, z1, x1, y1, z1, x0, y1, z1)

def info_quad(window_height, width, height):
    """ Рисует прямоугольную область в 2D режиме
    в верхнем-левом углу экрана """
    border = 10
    x0 = border
    x1 = x0 + width
    y1 = window_height - border
    y0 = y1 - height
    my_quad = [x0, y0, x1, y0, x1, y1, x0, y1]
    pyglet.gl.glColor4f(0.8, 0.9, 0.8, 0.6)
    pyglet.graphics.draw(4, pyglet.gl.GL_QUADS, ('v2i', my_quad))


def show_sight(x, y):
    """ Прицел в центре экрана
    :param x:
    :param y:
    :return:
    """
    pyglet.gl.glColor4f(0.0, 0.0, 0.0, 0.15)
    w = 10
    sight = (x+1, y-1, x+1, y-w, x+w, y-1, x-1, y-1, x-w, y-1, x-1, y-w,
             x+1, y+1, x+w, y+1, x+1, y+w, x-1, y+1, x-1, y+w, x-w, y+1)
    pyglet.graphics.draw(12, pyglet.gl.GL_TRIANGLES, ('v2i', sight))


def expand_IxI(descr_list, I):
    """ Декодирует список, описывающий в сжатой форме поверхность одной
        плитки в квадратную матрицу координат IxI (9х9)

        Если начало поверхности должно состоит из пропусков (нулей), тогда в
        декодируемом списке ведущим должен быть 0:
            m[0, 3, 5] - вначале будет 3 пропуска (нуля)
        Матрица из всех (81) нулей кодируется как m[0] или m[0,81], хотя
            такая поверхность не имеет смысла - ее нет.

        Матрица из 81-й единицы кодируется как m[] или m[81]
        В остальных позициях, кроме начальной, нулей быть не должно.
    """

    f = 1
    if descr_list:
        descr_list.reverse()
        Dp = descr_list.pop()
        if Dp == 0:
            f = 0
            Dp = descr_list.pop() if descr_list else 0
    else:
        Dp = 0

    IxI = []
    m_row = []
    for l in range(I):
        for c in range(I):
            m_row.append(f)
            if Dp:
                Dp -= 1
                if not Dp:
                    f = 0 if f == 1 else 1
                    Dp = descr_list.pop() if descr_list else 0
        IxI.append(m_row)
        m_row = []
    del(f, c, l, m_row, Dp)
    return IxI


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
    if isinstance(args[0], str) and typ is pyglet.gl.GLubyte:
        return (typ * len(args))(*[ord(c) for c in args])
    else:
        return (typ * len(args))(*args)


def compress_IxI(m):
    ''' Кодирует 2d матрицу IxI координат в сжатый список для хранения
        в базе данных
    '''
    line = []
    for r in range(len(m)):
        line += m[r]

    curr = line[0]
    rez = [0] if curr == 0 else []
    
    i = 0
    for n in range(len(line)):
        if curr == line[n]:
            i += 1
        else:
            rez.append(i)
            i = 1
            curr = line[n]

    return rez


def tex_coord(x, y, n=4):
    """ Генерирует две координаты прямоугольной области текстуры, загруженной
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
    return (x0, y0, x1, y1)


def get_texture_coordinates(top, down, side):
    """ Генерирует точки координат текстуры для параллелограмма, по
        координатам квадратов полей в текстурной карте с раздельным
        указанием текстур для верха, низа и боковых сторон.

        Возвращает список из 48 точек координат - 24 двухмерных координаты.

        sid_part - отделяемая часть по высоте (высота стороны параллелепипеда)

        x0 = x * m
        y0 = y * m
        x1 = x0 + m
        y1 = y0 + m
    """
    # число текстур по длине стороны общей картинки файла текстур
    m = 1.0 / rig.texture_rows

    x0, y0, x1, y1 = tex_coord(*top)
    t = (x0, y0, x1, y0, x1, y1, x0, y1)

    x0, y0, x1, y1 = tex_coord(*down)
    d = (x0, y0, x1, y0, x1, y1, x0, y1)

    x0, y0, x1, y1 = tex_coord(*side)
    y1 = (y1 - y0) * rig.height_to_length + y0
    s = (x0, y0, x1, y0, x1, y1, x0, y1)

    # r, l, d, t, b, f
    coords = [s[:], s[:], d[:], t[:], s[:], s[:]]
    del (t, d, s, x0, y0, x1, y1)
    return coords


# ============================================================================
#   Диагностика
# ============================================================================

if __name__ == "__main__":

    print('')
    descr_list = [0, 40, 1]
    print(descr_list)

    print('---')
    # Распаковка списка
    m_9x9 = expand_IxI(descr_list, 9)
    for n in range(len(m_9x9)):
        print(m_9x9[n])
    del(n)
    print('---')

    # Упаковка
    line = compress_IxI(m_9x9)
    print(line)

    print('')

    print('')
    descr_list = [40, 1]
    print(descr_list)

    print('---')
    # Распаковка списка
    m_9x9 = expand_IxI(descr_list, 9)
    for n in range(len(m_9x9)):
        print(m_9x9[n])
    del(n)
    print('---')

    # Упаковка
    line = compress_IxI(m_9x9)
    print(line)

    print('')
