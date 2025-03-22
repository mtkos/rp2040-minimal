TARGET = picolibc-example

SRC = main.c
SRC += ../boot2/boot2.s

include ../build.mk

FLAGS = -Os -specs=picolibc.specs -mcpu=cortex-m0plus -T../ld/Link-pico.ld -Wall -Wl,-Map,$(TARGET).map
