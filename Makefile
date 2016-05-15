CC = gcc
CFLAGS = -Wall -g

#all: bwt unbwt mtf unmtf huffman unhuffman libhuff.a
all: main libhuff.a

libhuff.a: huff.o
	rm -f libhuff.a
	ar -cq libhuff.a huff.o

main: main.c libhuff.a huffman.o
	$(CC) $(CFLAGS) main.c -o $@ huffman.o -L. -lhuff

#huffman: libhuff.a huffman.o
#	$(CC) $(CFLAGS) -o $@ huffman.o -L. -lhuff

#unhuffman: libhuff.a unhuffman.o
#	$(CC) $(CFLAGS) -o $@ unhuffman.o -L. -lhuff

#mtf: mtf.c
#	$(CC) $(CFLAGS) -o $@ mtf.c

#unmtf: unmtf.c
#	$(CC) $(CFLAGS) -o $@ unmtf.c

#bwt: bwt.c
#	$(CC) $(CFLAGS) -o $@ bwt.c

#unbwt: unbwt.c
#	$(CC) $(CFLAGS) -o $@ unbwt.c

clean:
	rm -f core *.o huffman unhuffman mtf unmtf bwt unbwt libhuff.a

depend:
	makedepend *.c

# DO NOT DELETE THIS LINE -- make depend depends on it.

bwt.o: /usr/include/stdio.h /usr/include/features.h
bwt.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
bwt.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
bwt.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
bwt.o: /usr/include/bits/typesizes.h /usr/include/libio.h
bwt.o: /usr/include/_G_config.h /usr/include/wchar.h
bwt.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
bwt.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
bwt.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
bwt.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
bwt.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
bwt.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
bwt.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
bwt.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
bwt.o: /usr/include/ctype.h /usr/include/xlocale.h /usr/include/string.h
bwt.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
bwt.o: /usr/include/bits/stat.h
huff.o: /usr/include/sys/param.h /usr/include/limits.h
huff.o: /usr/include/features.h /usr/include/bits/predefs.h
huff.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
huff.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
huff.o: /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h
huff.o: /usr/include/linux/limits.h /usr/include/bits/posix2_lim.h
huff.o: /usr/include/linux/param.h /usr/include/asm/param.h
huff.o: /usr/include/asm-generic/param.h /usr/include/sys/types.h
huff.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
huff.o: /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h
huff.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
huff.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
huff.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
huff.o: /usr/include/bits/pthreadtypes.h /usr/include/stdlib.h
huff.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
huff.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
huff.o: /usr/include/_G_config.h /usr/include/wchar.h
huff.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
huff.o: /usr/include/string.h /usr/include/xlocale.h /usr/include/ctype.h
huff.o: huff.h
huffman.o: /usr/include/sys/param.h /usr/include/limits.h
huffman.o: /usr/include/features.h /usr/include/bits/predefs.h
huffman.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
huffman.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
huffman.o: /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h
huffman.o: /usr/include/linux/limits.h /usr/include/bits/posix2_lim.h
huffman.o: /usr/include/linux/param.h /usr/include/asm/param.h
huffman.o: /usr/include/asm-generic/param.h /usr/include/sys/types.h
huffman.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
huffman.o: /usr/include/time.h /usr/include/endian.h
huffman.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
huffman.o: /usr/include/sys/select.h /usr/include/bits/select.h
huffman.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
huffman.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
huffman.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
huffman.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
huffman.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
huffman.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
huffman.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
huffman.o: /usr/include/xlocale.h /usr/include/ctype.h huff.h
mtf.o: /usr/include/stdlib.h /usr/include/features.h
mtf.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
mtf.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
mtf.o: /usr/include/gnu/stubs-64.h /usr/include/bits/waitflags.h
mtf.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
mtf.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
mtf.o: /usr/include/sys/types.h /usr/include/bits/types.h
mtf.o: /usr/include/bits/typesizes.h /usr/include/time.h
mtf.o: /usr/include/sys/select.h /usr/include/bits/select.h
mtf.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
mtf.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
mtf.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
mtf.o: /usr/include/_G_config.h /usr/include/wchar.h
mtf.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
mtf.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
mtf.o: /usr/include/bits/stat.h
unbwt.o: /usr/include/stdio.h /usr/include/features.h
unbwt.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
unbwt.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
unbwt.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
unbwt.o: /usr/include/bits/typesizes.h /usr/include/libio.h
unbwt.o: /usr/include/_G_config.h /usr/include/wchar.h
unbwt.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
unbwt.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
unbwt.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
unbwt.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
unbwt.o: /usr/include/sys/types.h /usr/include/time.h
unbwt.o: /usr/include/sys/select.h /usr/include/bits/select.h
unbwt.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
unbwt.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
unbwt.o: /usr/include/alloca.h /usr/include/ctype.h /usr/include/xlocale.h
unbwt.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
unbwt.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
unbwt.o: /usr/include/bits/posix2_lim.h /usr/include/fcntl.h
unbwt.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
unbwt.o: /usr/include/string.h
unhuffman.o: /usr/include/sys/param.h /usr/include/limits.h
unhuffman.o: /usr/include/features.h /usr/include/bits/predefs.h
unhuffman.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
unhuffman.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
unhuffman.o: /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h
unhuffman.o: /usr/include/linux/limits.h /usr/include/bits/posix2_lim.h
unhuffman.o: /usr/include/linux/param.h /usr/include/asm/param.h
unhuffman.o: /usr/include/asm-generic/param.h /usr/include/sys/types.h
unhuffman.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
unhuffman.o: /usr/include/time.h /usr/include/endian.h
unhuffman.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
unhuffman.o: /usr/include/sys/select.h /usr/include/bits/select.h
unhuffman.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
unhuffman.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
unhuffman.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
unhuffman.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
unhuffman.o: /usr/include/stdio.h /usr/include/libio.h
unhuffman.o: /usr/include/_G_config.h /usr/include/wchar.h
unhuffman.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
unhuffman.o: /usr/include/string.h /usr/include/xlocale.h
unhuffman.o: /usr/include/ctype.h huff.h
unmtf.o: /usr/include/stdlib.h /usr/include/features.h
unmtf.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
unmtf.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
unmtf.o: /usr/include/gnu/stubs-64.h /usr/include/bits/waitflags.h
unmtf.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
unmtf.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
unmtf.o: /usr/include/sys/types.h /usr/include/bits/types.h
unmtf.o: /usr/include/bits/typesizes.h /usr/include/time.h
unmtf.o: /usr/include/sys/select.h /usr/include/bits/select.h
unmtf.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
unmtf.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
unmtf.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
unmtf.o: /usr/include/_G_config.h /usr/include/wchar.h
unmtf.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
unmtf.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
unmtf.o: /usr/include/bits/stat.h
