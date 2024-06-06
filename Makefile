.PHONY : install static dynamic blob clean all

PATH_TO_APP=app
BIN=build/app-static build/app-dynamic build/app-blob build/blob.bin

PATH_TO_LIBZ=zlib
PATH_TO_LIBPNG=libpng
PATH_TO_FREETYPE=freetype

lib_make_a:
	$(MAKE) -C $(PATH_TO_LIBZ) static
	$(MAKE) -C $(PATH_TO_LIBPNG) static
	$(MAKE) -C $(PATH_TO_FREETYPE) static

lib_make_so:
	$(MAKE) -C $(PATH_TO_LIBZ) dynamic
	$(MAKE) -C $(PATH_TO_LIBPNG) dynamic
	$(MAKE) -C $(PATH_TO_FREETYPE) dynamic


static: lib_make_a
	$(MAKE) -C $(PATH_TO_APP) static

dynamic: lib_make_so
	$(MAKE) -C $(PATH_TO_APP) dynamic
	
blob: lib_make_a
	$(MAKE) -C $(PATH_TO_APP) blob
		
clean:
	rm -f $(BIN)
	$(MAKE) -C $(PATH_TO_APP) clean 

all: clean static dynamic blob
