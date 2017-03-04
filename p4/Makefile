# Michael Fortman Section 2
# Eric Eichstadt Section 2

all: cache1D cache2Drows cache2Dcols blockSize4 blockSize32 blockSize64 blockSize64rows blockSize64cols

cache1D: cache1D.c
	gcc -o cache1D cache1D.c -Wall -m32

cache2Drows: cache2Drows.c
	gcc -o cache2Drows cache2Drows.c -Wall -m32

cache2Dcols: cache2Dcols.c
	gcc -o cache2Dcols cache2Dcols.c -Wall -m32

blockSize4: cache1D.c
	/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 4 -ds 16384 -da 1 -db 4 -- cache1D

blockSize32: cache1D.c
	/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 32 -ds 16384 -da 1 -db 32 -- cache1D

blockSize64: cache1D.c
	/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 64 -ds 16384 -da 1 -db 64 -- cache1D

blockSize64rows: cache2Drows.c
	/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 64 -ds 16384 -da 1 -db 64 -- cache2Drows

blockSize64cols: cache2Dcols.c
	/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 64 -ds 16384 -da 1 -db 64 -- cache2Dcols
