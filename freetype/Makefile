.PHONY : install static dynamic blob clean all

BASE_SRCS = src/base/ftbase.c src/base/ftinit.c src/autofit/autofit.c src/base/ftbitmap.c src/base/ftglyph.c src/truetype/truetype.c src/type1/type1.c src/cff/cff.c src/cid/type1cid.c src/pfr/pfr.c src/type42/type42.c src/winfonts/winfnt.c src/gzip/ftgzip.c src/lzw/ftlzw.c src/pcf/pcf.c src/psaux/psaux.c src/psnames/psnames.c src/pshinter/pshinter.c src/raster/raster.c src/sfnt/sfnt.c src/bdf/bdf.c src/base/ftdebug.c src/smooth/smooth.c
OBJECTS=ftsystem.o ftbase.o ftinit.o autofit.o ftbitmap.o ftglyph.o truetype.o type1.o cff.o type1cid.o pfr.o type42.o winfnt.o ftgzip.o ftlzw.o pcf.o psaux.o psnames.o pshinter.o raster.o sfnt.o bdf.o ftdebug.o smooth.o
INCLUDES=-I./include/freetype/config -I./builds/unix -I./include 
CFLAGS=-fno-stack-protector -fno-exceptions -pie -fPIE -c -O2 -fPIC  "-DFT_CONFIG_CONFIG_H=<ftconfig.h>" -DFT2_BUILD_LIBRARY "-DFT_CONFIG_MODULES_H=<ftmodule.h>" "-DFT_CONFIG_OPTIONS_H=<ftoption.h>"

PATH_TO_BUILD=../build/

copy_a: libfreetype.a
	cp libfreetype.a $(PATH_TO_BUILD)

copy_so: libfreetype.so
	cp libfreetype.so $(PATH_TO_BUILD)

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -I./$(dir $@) $< -o $@	

ftsystem.o:
	gcc $(INCLUDES) -ansi $(CFLAGS) -DO_RDONLY=0 builds/unix/ftsystem.c -o ftsystem.o

libfreetype.a: ftsystem.o ${BASE_SRCS:c=o}
	ar cr $@ ${BASE_SRCS:c=o} ftsystem.o
	
libfreetype.so: ftsystem.o ${BASE_SRCS:c=o}
	gcc -shared ${BASE_SRCS:c=o} ftsystem.o -o libfreetype.so

static: libfreetype.a copy_a

dynamic:  libfreetype.so copy_so
	
blob: libfreetype.a copy_a

clean:
	rm -f *.a
	rm -f *.so
	rm -f *.o
	rm -f builds/unix/*.o
	rm -f ${BASE_SRCS:c=o}
	

all: clean static dynamic blob
