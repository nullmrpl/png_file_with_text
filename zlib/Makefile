.PHONY: static blob clean all

CC=gcc
OBJECTS=adler32.o crc32.o deflate.o infback.o inffast.o inflate.o inftrees.o trees.o zutil.o compress.o uncompr.o
CFLAFS=-fno-stack-protector -fno-exceptions -pie -fPIE -c -O2 -fPIC

PATH_TO_BUILD=../build/

copy_lib_a: libz.a
	cp libz.a $(PATH_TO_BUILD)

copy_lib_so: libz.so
	cp libz.so $(PATH_TO_BUILD)

.c.o:
	$(CC) $(CFLAFS) $< -o $@
	
libz.a: $(OBJECTS)
	ar rc libz.a $(OBJECTS)

static: libz.a copy_lib_a

libz.so:  $(OBJECTS)
	gcc -shared $(OBJECTS) -o libz.so	

dynamic: libz.so copy_lib_so

blob: libz.a

clean:
	rm -f *.a
	rm -f *.o
	
all: clean static blob