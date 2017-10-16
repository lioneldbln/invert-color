$1-The Valgrind Quick Start Guide
✦see http://valgrind.org/docs/manual/quick-start.html
✦running your program under Memcheck
>$ valgrind --leak-check=yes ./build/clrinvert ./res/tank.bmp ./output/img.bmp

$2-Compile with Debug option
>$ cmake -DCMAKE_BUILD_TYPE=Debug ..

