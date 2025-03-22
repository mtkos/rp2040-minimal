# utils

This map contains some utilitities. The pioasm is a dummy. You have to replace it by pioasm from the SDK, which I have not included, for copyright reasons. It is necessary for the ws2812d program
only. The program instr.py trims it output so that it can be used inside a normal (non-SDK) program. The program pad.py changes an input (binary) file to an assembly program consisting of exactly
256 bytes. It is necessary only for the picolibc-example program. The bin2uf2 program converts a binary to an UF2 file which will be accepted by the rp2040 bootrom. For this reason it adds
a CRC32 checksum of bytes 0...251 (which often contain the secondary bootloader) in bytes 252...255. The CRC32 parameters are taken from [rp2040], section 2.8.1.3.1.
