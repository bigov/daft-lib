__author__ = 'ib'

from random import randrange
from itertools import product

def p_gen(side_len):
    for p in product(range(-1,1), range(-1,1)):
        x, z = p
        y = randrange(2)
        yield ((x, y, z), None)

d = dict(p_gen(3))

print(d)
