TARGET = picolibc-example

SRC = main.c
SRC += ../boot2/bs2_default_padded_checksummed_patched.S

include ../build.mk

FLAGS = -Os -specs=picolibc.specs -mcpu=cortex-m0plus -T../ld/Link-pico.ld
