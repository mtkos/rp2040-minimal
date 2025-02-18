TARGET = ws2812d

SRC = main.c
SRC += startup.s
SRC += ../boot2/bs2_default_padded_checksummed.S

include ../build.mk

FLAGS += -Wl,-T../ld/Link.ld

main.c: $(TARGET).pio.h
	touch $@

$(TARGET).pio.h: $(TARGET).asm
	../utils/instr.py < $^ > $@

asm: $(TARGET).asm

$(TARGET).asm: $(TARGET).pio
	../utils/pioasm $^ > $@
