mkdir -p lib/linux

git submodule update --init --recursive

# Build SDL3
cd vendor/sdl
cmake -S . -B build/linux -DCMAKE_BUILD_TYPE=Release
cmake --build build/linux
cp build/linux/*.so ../../lib/linux
cp build/linux/*.so.* ../../lib/linux

# Build curl
cd ../curl
cmake -S . -B build/linux -DCMAKE_BUILD_TYPE=Release
cmake --build build/linux
cp build/linux/lib/*.so ../../lib/linux
cp build/linux/lib/*.so.* ../../lib/linux

# Build cglm
cd ../cglm
cmake -S . -B build/linux -DCMAKE_BUILD_TYPE=Release -DCGLM_STATIC=ON
cmake --build build/linux
cp build/linux/libcglm.a ../../lib/linux

cd ../..