.PHONY: install static dynamic blob clean all

CC=gcc
OBJECTS=png.o pngerror.o pngget.o pngmem.o pngpread.o pngread.o pngrio.o pngrtran.o pngrutil.o pngset.o pngtrans.o pngwio.o pngwrite.o pngwtran.o pngwutil.o
OBJECTS_ZLIB=../zlib/adler32.o ../zlib/crc32.o ../zlib/deflate.o ../zlib/infback.o ../zlib/inffast.o ../zlib/inflate.o ../zlib/inftrees.o ../zlib/trees.o ../zlib/zutil.o ../zlib/compress.o ../zlib/uncompr.o
CFLAGS=-fno-stack-protector -fno-exceptions -pie -fPIE -c -O2 -fPIC

PATH_TO_BUILD=../build/

copy_libpng_a: libpng.a
	cp libpng.a $(PATH_TO_BUILD)

copy_libpng_so: libpng.so
	cp libpng.so $(PATH_TO_BUILD)

.c.o:
	$(CC) $(CFLAGS) -I../zlib $< -o $@

#install: $(OBJECTS)

libpng.a: $(OBJECTS)
	ar cr libpng.a $(OBJECTS)

libpng.so:$(OBJECTS_ZLIB) $(OBJECTS)
	$(CC) -shared $(OBJECTS) $(OBJECTS_ZLIB) -o libpng.so -fPIC

static: libpng.a copy_libpng_a

dynamic: libpng.so copy_libpng_so

blob: libpng.a copy_libpng_a

clean:
	rm -f *.a
	rm -f *.so
	rm -f *.o
	
all: clean static dynamic blob
