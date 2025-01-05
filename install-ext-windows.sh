mkdir -p lib/windows

git submodule update --init --recursive

# Build SDL3
cd vendor/sdl
cmake -S . -B build/windows -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc
cmake --build build/windows --config Release
cp build/windows/*.dll.a ../../lib/windows
cp build/windows/*.dll ../../lib/windows

# Build SDL_Mixer
cd ../sdl_mixer
cmake -S . -B build/windows -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc
cmake --build build/windows --config Release
cp build/windows/*.dll.a ../../lib/windows
cp build/windows/*.dll ../../lib/windows

# Build cglm
cd ../cglm
cmake -S . -B build/windows -DCMAKE_BUILD_TYPE=Release -DCGLM_STATIC=ON -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc
cmake --build build/windows --config Release
cp build/windows/libcglm.a ../../lib/windows

cd ../..
