#!/usr/bin/env bash
echo "Building Corkus with CMake..."

mkdir -p build
cd build || exit 1

echo "Setting cmake build to Release..."
cmake -DCMAKE_BUILD_TYPE=Release -S ../../.. -B .

echo "Running cmake --build..."
cmake --build .

echo "Build Complete!"
echo "Executable @: $(pwd)"
