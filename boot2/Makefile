TARGET = boot2_w25q080
SRC = ${TARGET}.S

include ../build.mk

# FLAGS += -Wl,-T../ld/boot_stage2.ld -I../sdk_include
FLAGS +=  -I../sdk_include

pad: bs2_default_padded_checksummed.S

bs2_default_padded_checksummed.S: $(TARGET).bin
	../utils/pad_checksum -s 0xffffffff $^ $@

patch: bs2_default_padded_checksummed_patched.S

bs2_default_padded_checksummed_patched.S: bs2_default_padded_checksummed.S
	cp $^ $@; patch $@ bs2_default_padded_checksummed_patched.patch


