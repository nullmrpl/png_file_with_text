#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <resolv.h>

#include "png.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H

#ifdef _DYNAMIC_
#include <dlfcn.h>
#endif //_DYNAMIC_

struct Symbol
{
    int32_t pos_x;
    int32_t pos_y;
    int32_t width;
    int32_t height;
    FT_Glyph glyph;
};

unsigned long ToMs(struct timespec *tm) 
{
    return (unsigned long)(tm->tv_sec) * 1000
           + (unsigned long)(tm->tv_nsec) / 1000000;
}

#ifdef _DYNAMIC_

int (*SO_FT_Init_FreeType)(FT_Library*);
int (*SO_FT_New_Face)(FT_Library, const char*, FT_Long, FT_Face*);
int (*SO_FT_Set_Pixel_Sizes)(FT_Face, FT_UInt, FT_UInt);
int (*SO_FT_Load_Char)(FT_Face, FT_ULong, FT_Int32);
int (*SO_FT_Get_Char_Index)(FT_Face face, FT_ULong charcode);
int (*SO_FT_Get_Glyph)(FT_GlyphSlot slot, FT_Glyph* aglyph);
int (*SO_FT_Done_Glyph)(FT_Glyph glyph);
int (*SO_FT_Done_Face)(FT_Face face);
int (*SO_FT_Done_FreeType)(FT_Library library);
int (*SO_FT_Get_Kerning)(FT_Face face, FT_UInt left_glyph, FT_UInt right_glyph, FT_UInt kern_mode, FT_Vector* akerning);

void* (*SO_png_create_write_struct)(const char*, void*, void*, void*);
void* (*SO_png_create_info_struct)(void*);
void (*SO_png_init_io)(void*, void*);
void (*SO_png_set_IHDR)(void*, void*, unsigned int, unsigned int, int, int, int, int, int);
void (*SO_png_set_text)(void*, png_infop, png_textp, int);
void (*SO_png_write_end)(void*, void*);
void (*SO_png_write_row)(png_structp png_ptr, png_bytep row);
void (*SO_png_free_data)(png_structp png_ptr, png_infop info_ptr, png_uint_32 free_me, int num);
void (*SO_png_destroy_write_struct)(void*, void*);
void (*SO_png_write_info)(png_structp png_ptr, png_infop info_ptr);

#define FT_Init_FreeType SO_FT_Init_FreeType
#define FT_New_Face SO_FT_New_Face
#define FT_Set_Pixel_Sizes SO_FT_Set_Pixel_Sizes
#define FT_Load_Char SO_FT_Load_Char
#define FT_Get_Char_Index SO_FT_Get_Char_Index
#define FT_Get_Glyph SO_FT_Get_Glyph
#define FT_Done_Glyph SO_FT_Done_Glyph
#define FT_Done_Face SO_FT_Done_Face
#define FT_Done_FreeType SO_FT_Done_FreeType
#define FT_Get_Kerning SO_FT_Get_Kerning

#define png_write_info SO_png_write_info
#define png_create_write_struct SO_png_create_write_struct
#define png_create_info_struct SO_png_create_info_struct
#define png_init_io SO_png_init_io
#define png_set_IHDR SO_png_set_IHDR
#define png_set_text SO_png_set_text
#define png_write_end SO_png_write_end
#define png_write_row SO_png_write_row
#define png_free_data SO_png_free_data
#define png_destroy_write_struct SO_png_destroy_write_struct

#endif //_DYNAMIC_

#ifdef _BLOB_

#include <sys/stat.h>

void** glob_functions;

#define N_CLOCK 0
#define N_PUTS 1
#define N_STRLEN 2
#define N_STRRCHR 3
#define N_STPCPY 4
#define N_STRSTR 5
#define N_GETENV 6
#define N_MALLOC 7
#define N_STRNCMP 8
#define N_MEMCHR 9
#define N_STRCMP 10
#define N_MEMSET 11
#define N_STRNCPY 12
#define N_MMAP 13
#define N_REALLOC 14
#define N_MEMMOVE 15
#define N_FREXP 16
#define N_MODF 17
#define N_POW 18
#define N_MEMCPY 19
#define N_FPUTC 20
#define N_MEMCMP 21
#define N_FREAD 22
#define N_GMTIME 23
#define N_FOPEN 24
#define N_FERROR 25
#define N_FCLOSE 26
#define N_REMOVE 27
#define N_MUNMAP 28
#define N_FREE 29
#define N_FWRITE 30
#define N_FFLUSH 31
#define N_STRTOD 32
#define N_STRERROR 33
#define N_ABORT 34
#define N_READ 35
#define N_STRTOL 36
#define N___MEMCPY_CHK 37
#define N_QSORT 38
#define N_FSTAT 39
#define N_STDERR 41
#define N___LONGJMP_CHK 43
#define N___SPRINTF_CHK 44
#define N_STRCPY 45
#define N__SETJMP 46
#define N___ERRNO_LOCATION 47
#define N_CLOSE 48
#define N___FPRINTF_CHK 49
#define N_OPEN 50

clock_t clock(void) 
{
    return ((clock_t(*)(void))glob_functions[N_CLOCK])();
}

int puts(const char* str) 
{
    return ((int (*)(const char*))glob_functions[N_PUTS])(str);
}

size_t strlen(const char* str) 
{
    return ((size_t(*)(const char*))glob_functions[N_STRLEN])(str);
}

char* strrchr(const char* str, int ch) 
{
    return ((char* (*)(const char*, int))glob_functions[N_STRRCHR])(str, ch);
}

char* strstr(const char* str1, const char* str2) 
{
    return ((char* (*)(const char*, const char*))glob_functions[N_STRSTR])(str1, str2);
}

char* getenv(const char* name) 
{
    return ((char* (*)(const char*))glob_functions[N_GETENV])(name);
}

int strncmp(const char* str1, const char* str2, size_t count) 
{
    return ((int (*)(const char*, const char*, size_t))glob_functions[N_STRNCMP])(str1, str2, count);
}

void* memchr(const void* buffer, int ch, size_t count) 
{
    return ((void* (*)(const void*, int, size_t))glob_functions[N_MEMCHR])(buffer, ch, count);
}

int strcmp(const char* str1, const char* str2) 
{
    return ((int (*)(const char*, const char*))glob_functions[N_STRCMP])(str1, str2);
}

void* memset(void* buf, int ch, size_t count) 
{
    return ((void* (*)(void*, int, size_t))glob_functions[N_MEMSET])(buf, ch, count);
}

char* strncpy(char* dest, const char* source, size_t count) 
{
    return ((char* (*)(char*, const char*, size_t))glob_functions[N_STRNCMP])(dest, source, count);
}

void* mmap(void* start, size_t length, int prot, int flags, int fd, off_t offset) 
{
    return ((char* (*)(void*, size_t, int, int, int, off_t))glob_functions[N_MMAP])(start, length, prot, flags, fd, offset);
}

void* realloc(void* ptr, size_t newsize) 
{
    return ((void* (*)(void*, size_t))glob_functions[N_REALLOC])(ptr, newsize);
}

void* memmove(void* dest, const void* source, size_t count) 
{
    return ((void* (*)(void*, const void*, size_t))glob_functions[N_MEMMOVE])(dest, source, count);
}

double frexp(double num, int* exp) 
{
    return ((double (*)(double, int*))glob_functions[N_FREXP])(num, exp);
}

double modf(double num, double* i) 
{
    return ((double (*)(double, double*))glob_functions[N_MODF])(num, i);
}

double pow(double base, double exp) 
{
    return ((double (*)(double, double))glob_functions[N_POW])(base, exp);
}

int fputc(int ch, FILE* stream) 
{
    return ((int (*)(int, FILE*))glob_functions[N_FPUTC])(ch, stream);
}

int memcmp(const void* buf1, const void* buf2, size_t count) 
{
    return ((int (*)(const void*, const void*, size_t))glob_functions[N_MEMCMP])(buf1, buf2, count);
}

size_t fread(void* buf, size_t size, size_t count, FILE* stream) 
{
    return ((size_t(*)(void*, size_t, size_t, FILE*))glob_functions[N_FREAD])(buf, size, count, stream);
}

struct tm* gmtime(const time_t* time) 
{
    return ((struct tm* (*)(const time_t*))glob_functions[N_GMTIME])(time);
}

FILE* fopen(const char* fname, const char* mode) 
{
    return ((FILE * (*)(const char*, const char*))glob_functions[N_FOPEN])(fname, mode);
}

int munmap(void* start, size_t length) 
{
    return ((int (*)(void*, size_t))glob_functions[N_MUNMAP])(start, length);
}

void free(void* ptr) 
{
    return ((void (*)(void*))glob_functions[N_FREE])(ptr);
}

size_t fwrite(const void* buf, size_t size, size_t count, FILE* stream) 
{
    return ((size_t(*)(const void*, size_t, size_t, FILE*))glob_functions[N_FWRITE])(buf, size, count, stream);
}

int fflush(FILE* stream) 
{
    return ((int (*)(FILE*))glob_functions[N_FFLUSH])(stream);
}

void* memcpy(void* dest, const void* source, size_t count) 
{
    return ((void* (*)(void*, const void*, size_t))glob_functions[N_MEMCPY])(dest, source, count);
}

void* malloc(size_t size) 
{
    return ((void* (*)(size_t))glob_functions[N_MALLOC])(size);
}

int fclose(FILE* fp) 
{
    return ((int (*)(FILE*))glob_functions[N_FCLOSE])(fp);
}

int ferror(FILE* stream) 
{
    return ((int(*)(FILE*))glob_functions[N_FERROR])(stream);
}

ssize_t read(int fd, void* buf, size_t count) 
{
    return ((ssize_t(*)(int, void*, size_t))glob_functions[N_READ])(fd, buf, count);
}

long int strtol(const char* str, char** endptr, int base) 
{
    return ((long int (*)(const char*, char**, int))glob_functions[N_STRTOL])(str, endptr, base);
}

int __fprintf_chk(FILE* stream, int flag, const char* format, ...)
{

}

int _setjmp(jmp_buf env)
{
    return ((int (*)(jmp_buf env))glob_functions[N__SETJMP])(env);
}

void abort() 
{
    ((void (*)())glob_functions[N_ABORT])();
}

double strtod(const char* str, char** endptr) 
{
    return ((double (*)(const char*, char**))glob_functions[N_STRTOD])(str, endptr);
}

int remove(const char* pathname) 
{
    return ((int (*)(const char*))glob_functions[N_REMOVE])(pathname);
}

int open(const char* pathname, int flags) 
{
    return ((int (*)(const char*, int))glob_functions[N_OPEN])(pathname, flags);
}

int* __errno_location(void) 
{
    return ((int* (*)())glob_functions[N___ERRNO_LOCATION])();
}

FILE* stderr;

void qsort(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)) 
{
    return ((void (*)(void*, size_t, size_t, int (*)(const void*, const void*)))glob_functions[N_QSORT])(base, num, size, compar);
}

int close(int fd) 
{
    return ((int (*)(int))glob_functions[N_CLOSE])(fd);
}

int __sprintf_chk(char* str, int flag, size_t strlen, const char* format, ...) 
{

}

int fstat(int fd, struct stat *buf) 
{
    return ((int (*)(int, struct stat*))glob_functions[N_FSTAT])(fd, buf);
}

void* __memcpy_chk(void* dest, const void* src, size_t len, size_t destlen) 
{

}

char* strcpy(char* destination, const char* source) 
{
    return ((char* (*)(char*, const char*))glob_functions[N_STRCPY])(destination, source);
}

void __longjmp_chk() 
{

}

char* strerror(int errnum) 
{
    return ((char* (*)(int))glob_functions[N_STRERROR])(errnum);
}

char* stpcpy(char* dest, const char* src) 
{
    return ((char* (*)(char*, const char*))glob_functions[N_STPCPY])(dest, src);
}

#endif// _BLOB_

FT_Glyph GetGlyph(FT_Face face, uint32_t charcode)
{
    FT_Load_Char(face, charcode, FT_LOAD_RENDER);
    FT_Glyph glyph = 0;
    FT_Get_Glyph(face->glyph, &glyph);
    return glyph;
}

FT_Pos GetKerning(FT_Face face, uint32_t left_charcode, uint32_t right_charcode)
{
    FT_UInt leftIndex = FT_Get_Char_Index(face, left_charcode);
    FT_UInt rightIndex = FT_Get_Char_Index(face, right_charcode);
    FT_Vector delta;
    FT_Get_Kerning(face, leftIndex, rightIndex, FT_KERNING_DEFAULT, &delta);
    return delta.x;
}

#ifndef _BLOB_
float *TextToFloatBuf(int* width, int* height, const char* font_file, const char* str, unsigned long* load_time)
#else
float *TextToFloatBuf(int* width, int* height, const char* font_file, const char* str)
#endif //_BLOB
{
	static const size_t MAX_SYMBOLS_COUNT = 128;
#ifdef _DYNAMIC_
	struct timespec t1, t2; 
	clock_gettime(CLOCK_REALTIME, &t1);
#endif //_BLOB
		
	int status;
	FT_Library ftLibrary = 0;
	FT_Init_FreeType(&ftLibrary);
	FT_Face ft_face = 0;
	float *image = NULL;
	*width = 0;
	*height = 0;
	if ((status = FT_New_Face(ftLibrary, font_file, 0, &ft_face)) != 0) 
	{
	#ifndef _BLOB_
		printf("Font file ERROR\n");
	#endif //_BLOB
		goto final1;
	}
#ifdef _DYNAMIC_
	clock_gettime(CLOCK_REALTIME, &t2);
	*load_time += ToMs(&t2) - ToMs(&t1);
#endif //_BLOB
	
	if ((FT_Set_Pixel_Sizes(ft_face, 100, 0)) != 0) 
	{
        	goto final1;
	}
	const size_t str_len = strlen(str);
	if (str_len >= MAX_SYMBOLS_COUNT) 
	{
		#ifndef _BLOB_
		printf("Error: too long string. Should be < %zu", MAX_SYMBOLS_COUNT);
		#endif //_BLOB		
        	goto final1;
        }
        
        struct Symbol* symbols = (struct Symbol*)malloc(MAX_SYMBOLS_COUNT * sizeof(struct Symbol));
	size_t num_symbols = 0;
	int32_t left = INT_MAX;
	int32_t top = INT_MAX;
	int32_t bottom = INT_MIN;
	uint32_t prev_charcode = 0;
	int32_t pos_x = 0;
	
	for (size_t i = 0; i < str_len; ++i) 
	{
        	const uint32_t charcode = (uint32_t) str[i];
        	FT_Glyph glyph = GetGlyph(ft_face, charcode);
        	if (!glyph) { continue; }
        	if (prev_charcode) 
        	{
        		pos_x += GetKerning(ft_face, prev_charcode, charcode);
        	}
        	prev_charcode = charcode;
        	
        	struct Symbol *symb = &(symbols[num_symbols++]);
        	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;
        	symb->pos_x = (pos_x >> 6) + bitmap_glyph->left;
		symb->pos_y = -bitmap_glyph->top;
		symb->width = bitmap_glyph->bitmap.width;
        	symb->height = bitmap_glyph->bitmap.rows;
        	symb->glyph = glyph;
		pos_x += glyph->advance.x >> 10;
		left = MIN(left, symb->pos_x);
		top = MIN(top, symb->pos_y);
		bottom = MAX(bottom, symb->pos_y + symb->height);
	}
	for (size_t i = 0; i < num_symbols; ++i) 
	{
        	symbols[i].pos_x -= left;
    	}
    	
    	const struct Symbol *last_symbol = &(symbols[num_symbols - 1]);
    	const int32_t image_w = last_symbol->pos_x + last_symbol->width;
    	const int32_t image_h = bottom - top;
    	image = (float*)malloc(image_w * image_h * sizeof(float));
    	for (size_t i = 0; i < num_symbols; ++i) 
    	{
        	const struct Symbol *symb = symbols + i;
		FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)symb->glyph;
        	FT_Bitmap bitmap = bitmapGlyph->bitmap;
		for (int32_t srcY = 0; srcY < symb->height; ++srcY) 
		{
			const int32_t dstY = symb->pos_y + srcY - top;
			for (int32_t srcX = 0; srcX < symb->width; ++srcX) 
			{
				const float c = bitmap.buffer[srcX + srcY * bitmap.pitch];
				if (c == 0) continue;
				const float a = c / 255.0f;
				const int32_t dstX = symb->pos_x + srcX;
				image[dstX + dstY * image_w] = a * dstY / 255.0f + 0.10f;
			}
		}
	}
	for (size_t i = 0; i < num_symbols; ++i) 
	{
        	FT_Done_Glyph(symbols[i].glyph);
    	}
    	free(symbols);
	if (!status) 
	{
        	*width = image_w;
        	*height = image_h;
    	}

final1:
    	if (ft_face) FT_Done_Face(ft_face);
    	if (ftLibrary) FT_Done_FreeType(ftLibrary);
	if (!status) return image;
	return NULL;
}

void SetRGB(png_byte *ptr, float val)
{
    int v = (int)(val * 767);
    if (v < 0) v = 0;
    if (v > 767) v = 767;
    int offset = v % 256;
    if(offset>0)
    {ptr[0] = 255; ptr[1] = 255; ptr[2] = 255;}
    else {ptr[0] = 0; ptr[1] = 0; ptr[2] = 0;}
}

#ifndef _BLOB_
void WriteImage(const char* filename, int width, int height, float *buffer, const char* title, unsigned long* load_time)
#else
void WriteImage(const char* filename, int width, int height, float *buffer, const char* title)
#endif //_BLOB
{
#ifndef _BLOB_
    	struct timespec t1, t2;
    	clock_gettime(CLOCK_REALTIME, &t1);
#endif //_BLOB
    	
    	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;
	
	fp = fopen(filename, "wb");
	if (fp == NULL) 
	{
		#ifndef _BLOB_
		printf("Error: could not open file %s for writing\n", filename);
		#endif //_BLOB        	
        	goto final2;
    	}
    	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    	if (png_ptr == NULL) 
    	{
    		#ifndef _BLOB_
		printf("Error: could not allocate write struct\n");
		#endif //_BLOB    		
		goto final2;
	}
	
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) 
	{
		#ifndef _BLOB_
		printf("Error: could not allocate info struct\n");
		#endif //_BLOB
        	goto final2;
        }
    	
    	png_init_io(png_ptr, fp);
    	
#ifndef _BLOB_
    	clock_gettime(CLOCK_REALTIME, &t2);
    	*load_time = ToMs(&t2) - ToMs(&t1);
#endif //_BLOB
    	
    	png_set_IHDR(png_ptr, info_ptr, width, height,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	if (title != NULL) 
	{
        	png_text title_text;
        	title_text.compression = PNG_TEXT_COMPRESSION_NONE;
        	title_text.key = (char*)"Title";
       	title_text.text = (char*)title;
      		png_set_text(png_ptr, info_ptr, &title_text, 1);
      	}
      	png_write_info(png_ptr, info_ptr);
	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep)malloc(3 * width * sizeof(png_byte));
	// Write image data
	int x, y;
	for (y=0 ; y<height ; y++) 
	{
		for (x=0 ; x<width ; x++) 
		{
			SetRGB(&(row[x * 3]), buffer[y * width + x]);
        	}
        	png_write_row(png_ptr, row);
    	}
	// End write
	png_write_end(png_ptr, NULL);

final2:
	if (fp != NULL) fclose(fp);
    	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (row != NULL) free(row);
	return;
}

#ifdef _BLOB_
int main(int argc, char* argv[], void** functions) 
{
    glob_functions = functions;

#else //no _BLOB_

int main(int argc, char *argv[], char *envp[]) 
{
    struct timespec t1, t2;
    unsigned long load_time = 0, tmp_time = 0, total_time = 0;

    clock_gettime(CLOCK_REALTIME, &t1);
    
    if (argc != 4) 
    {
    	printf("Error: not enough\\to many arguments\n");
    	return 1;
    }
       
#ifdef _DYNAMIC_
	struct timespec t3;
	void *ft_handle = NULL, *lz_handle = NULL, *png_handle = NULL;
	lz_handle = dlopen("./libz.so", RTLD_LAZY);
	png_handle = dlopen("./libpng.so", RTLD_LAZY);
	ft_handle = dlopen("./libfreetype.so", RTLD_LAZY);
	
    	SO_FT_Init_FreeType = dlsym(ft_handle, "FT_Init_FreeType");
    	SO_FT_New_Face = dlsym(ft_handle, "FT_New_Face");
    	SO_FT_Set_Pixel_Sizes = dlsym(ft_handle, "FT_Set_Pixel_Sizes");
    	SO_FT_Load_Char = dlsym(ft_handle, "FT_Load_Char");
    	SO_FT_Get_Char_Index = dlsym(ft_handle, "FT_Get_Char_Index");
    	SO_FT_Get_Glyph = dlsym(ft_handle, "FT_Get_Glyph");
    	SO_FT_Done_Glyph = dlsym(ft_handle, "FT_Done_Glyph");
    	SO_FT_Done_Face = dlsym(ft_handle, "FT_Done_Face");
    	SO_FT_Done_FreeType = dlsym(ft_handle, "FT_Done_FreeType");
    	SO_FT_Get_Kerning = dlsym(ft_handle, "FT_Get_Kerning");

    	SO_png_create_write_struct = dlsym(png_handle, "png_create_write_struct");
    	SO_png_create_info_struct = dlsym(png_handle, "png_create_info_struct");
    	SO_png_init_io = dlsym(png_handle, "png_init_io");
    	SO_png_set_IHDR = dlsym(png_handle, "png_set_IHDR");
    	SO_png_set_text = dlsym(png_handle, "png_set_text");
    	SO_png_write_end = dlsym(png_handle, "png_write_end");
    	SO_png_write_row = dlsym(png_handle, "png_write_row");
    	SO_png_free_data = dlsym(png_handle, "png_free_data");
    	SO_png_destroy_write_struct = dlsym(png_handle, "png_destroy_write_struct");
    	SO_png_write_info = dlsym(png_handle, "png_write_info");
    			
	if (!ft_handle || !png_handle || !lz_handle) 
	{
		fputs(dlerror(), stderr);
        	fputs("\n", stderr);
        	exit(1);
    	}
    	clock_gettime(CLOCK_REALTIME, &t3);
    	load_time += ToMs(&t3) - ToMs(&t1);
#endif //_DYNAMIC_

    printf("Creation of png file\n");
    
#endif //_BLOB_

    const char* font = argv[1];
    const char* str = argv[2];
    const char* new_file = argv[3];
    int width = 0;
    int height = 0;
    
#ifndef _BLOB_
    float *buffer = TextToFloatBuf(&width, &height, font, str, &load_time);
#else
    float *buffer = TextToFloatBuf(&width, &height, font, str);
#endif //_BLOB_
    
    
    if (buffer == NULL) 
    {
#ifdef _DYNAMIC_
	dlclose(ft_handle);
	dlclose(png_handle);
	dlclose(lz_handle);
#endif //_DYNAMIC_
        return 1;
    }
#ifndef _BLOB_
    printf("File created, creation of note\n");
#endif //_BLOB_

#ifndef _BLOB_
    WriteImage(new_file, width, height, buffer, "Test", &tmp_time);
#else
    WriteImage(new_file, width, height, buffer, "Test");
#endif //_BLOB_

    free(buffer);
    
#ifndef _BLOB_
    clock_gettime(CLOCK_REALTIME, &t2);
    //load_time += tmp_time;
    total_time = ToMs(&t2) - ToMs(&t1);
    printf("Success!!!\nLoad time: %lu ms\nTotal time: %lu ms\n", load_time,total_time);
#endif //_BLOB_
#ifdef _DYNAMIC_
	dlclose(ft_handle);
	dlclose(png_handle);
	dlclose(lz_handle);
#endif //_DYNAMIC_
    return 0;
}
