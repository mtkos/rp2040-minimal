#!/usr/bin/python3

from sys import argv

def pad(l):
    return l + bytes(256 - len(l))

f = open(argv[1], 'rb')
l = pad(f.read())
f.close()

def word(x):
    return x.to_bytes(4, 'little')

f = open(argv[2], 'w')
f.write('// Padded version of: {}\n\n'.format(argv[1]))

f.write('.cpu cortex-m0plus\n')
f.write('.thumb\n\n')

f.write('.section .text.init.enter, "ax"\n\n')

for i in range(0, 256, 16):
    f.write('.byte')
    for j in l[i:i + 15]:
        f.write(' {0:#04x},'.format(j))
    f.write(' {0:#04x}\n'.format(l[i + 15]))
f.close()
