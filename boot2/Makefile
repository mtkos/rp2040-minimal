TARGET = boot2

SRC = ${TARGET}.c

include ../build.mk

FLAGS += -T../ld/Link.ld

$(TARGET).s: $(TARGET).bin
	../utils/pad.py $^ $@

pad: $(TARGET).s
