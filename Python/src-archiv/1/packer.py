#-*- coding:utf-8 -*-

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
