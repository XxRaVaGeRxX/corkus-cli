echo Building Corkus with CMake...

if not exist build mkdir build
cd build

echo Setting cmake build to Release...
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .

echo Running cmake build...
cmake --build .

echo Build Complete!
echo Executable @: %cd%
echo Run with: Corkus.exe

pause
