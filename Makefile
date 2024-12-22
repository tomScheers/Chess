EXE_NAME = chess

LINUX_SRC = src/system/platform_impl_sdl.c

SRC = src/game/entry.c

INCLUDE = -Iinclude \
	-Ivendor/sokol -Ivendor/sdl/include -Ivendor/cglm/include

LIBS = -lSDL3 -lcglm

CFLAGS = -O2 -Wall -Wextra -g

all: linux

linux:
	mkdir -p bin
	cp lib/linux/*.so bin
	cp lib/linux/*.so.* bin

	bear -- ccache clang -target x86_64-linux-gnu -Wl,-rpath=. $(CFLAGS) -o bin/$(EXE_NAME).x86_64 $(SRC) $(LINUX_SRC) $(INCLUDE)

.PHONY: linux