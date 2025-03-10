#!/usr/bin/python3

from sys import argv
from crcmod import mkCrcFun

def pad(l):
    return l + bytes(252 - len(l))

f = open(argv[1], 'rb')
l = pad(f.read())
f.close()

crc = mkCrcFun(poly=0x104c11db7, rev=False, initCrc=0xffffffff, xorOut=0x00000000)

def word(x):
    return x.to_bytes(4, 'little')

l = l + word(crc(l))

f = open(argv[2], 'w')
f.write('// Padded and checksummed version of: {}\n\n'.format(argv[1]))

f.write('.cpu cortex-m0plus\n')
f.write('.thumb\n\n')

f.write('.section .boot2, "ax"\n\n')

for i in range(0, 256, 16):
    f.write('.byte')
    for j in l[i:i + 15]:
        f.write(' {0:#0{1}x},'.format(j, 4))
    f.write(' {0:#0{1}x} \n'.format(l[i + 15], 4))
f.close()
