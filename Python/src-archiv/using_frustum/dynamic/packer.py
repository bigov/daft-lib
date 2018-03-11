#-*- coding:utf-8 -*-

import pyglet

def info_quad(window_height, width, height):
    ''' Рисует прямоугольную область в 2D режиме
    в верхнем-левом углу экрана '''
    border = 10
    x0 = border
    x1 = x0 + width
    y1 = window_height - border
    y0 = y1 -  height
    my_quad = [x0,y0, x1,y0, x1,y1, x0,y1]
    pyglet.graphics.draw(4, pyglet.gl.GL_QUADS, 
        ('v2i', my_quad), 
        ('c4f', (0.8, 0.9, 0.8, 0.6,
                 0.8, 0.9, 0.8, 0.6,
                 0.8, 0.9, 0.8, 0.6,
                 0.8, 0.9, 0.8, 0.6 ))
    )

def expand_IxI(descr_list, I):
    ''' Декодирует список, описывающий в сжатой форме поверхность одной
        плитки в квадратную матрицу координат IxI (9х9)

        Если начало поверхности должно состоит из пропусков (нулей), тогда в
        декодируемом списке ведущим должен быть 0:
            m[0, 3, 5] - вначале будет 3 пропуска (нуля)
        Матрица из всех (81) нулей кодируется как m[0] или m[0,81], хотя
            такая поверхность не имеет смысла - ее нет.

        Матрица из 81-й единицы кодируется как m[] или m[81]
        В остальных позициях, кроме начальной, нулей быть не должно.
    '''

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
