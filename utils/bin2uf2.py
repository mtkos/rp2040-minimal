#!/usr/bin/python3

from sys import argv

first_magic_number = 0x0a324655
second_magic_number = 0x9e5d5157
flags = 0x00002000
load_address = 0x10000000
block_size = 256
family_id = 0xe48bff56
padding = b'\x00'*(476 - 256)
final_magic_number = 0x0ab16f30

def pad(l):
    if len(l)%256 == 0:
        return l
    else:
        return l + b'\x00'*(256 - len(l)%256)

def word(x):
    return x.to_bytes(4, 'little')

def uf2block(blocknumber, nblocks, block):
     return word(first_magic_number) + word(second_magic_number) + word(flags) + word(load_address + n*0x100) + \
            word(block_size) + word(blocknumber) + word(nblocks) + word(family_id) + block + padding + word(final_magic_number)

f = open(argv[1], "rb")
l = pad(f.read())
f.close()

blocks = [l[i:i + 256] for i in range(0, len(l), 256)]
nblocks = len(blocks)

f = open(argv[2], "wb")
for n in range(nblocks):
    f.write(uf2block(n, nblocks, blocks[n]))
f.close()
