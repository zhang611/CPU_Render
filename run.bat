rm -r build
cmake -B build
cmake --build build --config Release
.\build\Release\CPU_Render.exe