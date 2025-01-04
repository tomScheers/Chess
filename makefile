NAME = chess

FLAGS = -std=c11 -O2
LIBS = -lm -lcglm -lSDL3 -lpthread -ldl
DIRS = -Iinclude -Ivendor/sdl/include -Ivendor/cglm/include -Ivendor/stb

BUILD_TARGET=SOMETHING

GAME_SRC = src/game/entry.c src/game/cache.c \
	src/game/gameobjects/*.c include/engine/engine.c

APP_SRC = $(GAME_SRC) \
	src/app/main.c src/game_engine/gfx.c src/game_engine/components.c

SRC = src/glad/glad.c \
	$(APP_SRC)

IMPL_DESKTOP = src/game_engine/app_desktop.c \
	src/game_engine/renderer_gl.c src/game_engine/renderer_gl/*.c

all: linux

linux:
	mkdir -p bin/linux
	bear -- ccache clang -target x86_64-linux-gnu -Wl,-rpath=. $(FLAGS) -o bin/linux/$(NAME) $(SRC) $(IMPL_DESKTOP) $(DIRS) -Llib/linux $(LIBS) -lGL
	cp -f lib/linux/*.so bin/linux
	cp -f lib/linux/*.so.* bin/linux
	mkdir -p bin/linux/data
	mkdir -p data/desktop
	rsync -a --delete ./data/desktop/ ./bin/linux/data/

windows:
	mkdir -p bin/windows
	bear -- ccache clang -target x86_64-windows-gnu $(FLAGS) -o bin/windows/$(NAME).exe $(SRC) $(IMPL_DESKTOP) $(DIRS) -Llib/windows $(LIBS) -lopengl32
	cp -f lib/windows/*.dll bin/windows
	mkdir -p bin/windows/data
	mkdir -p data/desktop
	rsync -a --delete ./data/desktop/ ./bin/windows/data/

# TODO: Add Emscripten/Web support

.PHONY: linux windows