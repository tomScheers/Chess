ROOT = ../..

SRC = \
	$(ROOT)/src/main.c \
	$(ROOT)/src/platform_impl_sdl.c

DIR = \
	-I$(ROOT)/src \
	-I$(ROOT)/vendor/cglm/include -Ivendor/sdl/include \
	-L$(ROOT)/lib/linux

LIB = \
	-lSDL3 -lcglm

all: linux

linux:
	bear -- gcc -O3 -o chess $(SRC) $(DIR) $(LIB)

.PHONY: linux