CC=gcc
CFLAGS=-c -Wall -O
CFLAGS_STATIC=-Wall 
CFLAGS_BLOB=-fno-stack-protector -fno-exceptions -nostdlib -pie -fPIE -fPIC -w -e main -D_BLOB_

LIBPNG_INCLUDE=../libpng
FTYPE_INCLUDE=../freetype/include

PATH_TO_LIBZ=zlib
PATH_TO_LIBPNG=libpng
PATH_TO_FREETYPE=freetype
PATH_TO_FREETYPE_LIB=freetype/install/lib

LIBZ_STATIC=libz.a
LIBPNG_STATIC=libpng.a
FTYPE_STATIC=libfreetype.a

SOURCES=Main.c
SOURCES_LOADER=../elfloader/elf_loader.c ../elfloader/main.c ../elfloader/wheelc/list.c
APP_BLOB=../build/app-blob
BLOB_BIN=../build/blob.bin

APP_OBJECTS=Main.o
OUT_FILE_STATIC=../build/app-static
OUT_FILE_DYNAMIC=../build/app-dynamic


all: static dynamic blob clean

$(OUT_FILE_STATIC):
	$(CC) $(CFLAGS) -I$(LIBPNG_INCLUDE) -I$(FTYPE_INCLUDE) $(SOURCES)
	$(CC) -static $(CFLAGS_STATIC) $(APP_OBJECTS) ../$(PATH_TO_LIBPNG)/$(LIBPNG_STATIC) ../$(PATH_TO_LIBZ)/$(LIBZ_STATIC) ../$(PATH_TO_FREETYPE_LIB)/$(FTYPE_STATIC) -lm -o $(OUT_FILE_STATIC)


static: $(OUT_FILE_STATIC)

$(OUT_FILE_DYNAMIC):
	$(CC) -I$(FTYPE_INCLUDE) -I$(LIBPNG_INCLUDE) -D_DYNAMIC_ $(SOURCES) -lm -ldl -o $(OUT_FILE_DYNAMIC)

dynamic: $(OUT_FILE_DYNAMIC)

$(BLOB_BIN):
	$(CC) $(SOURCES_LOADER) -lm -ldl -o $(APP_BLOB)
	$(CC) $(SOURCES) -I$(FTYPE_INCLUDE) -I$(LIBPNG_INCLUDE) \
		../$(PATH_TO_FREETYPE)/$(FTYPE_STATIC) ../$(PATH_TO_LIBPNG)/$(LIBPNG_STATIC) ../$(PATH_TO_LIBZ)/$(LIBZ_STATIC) \
		$(CFLAGS_BLOB) -o $(BLOB_BIN)	

blob: $(BLOB_BIN)


clean:
	rm -f *.o
