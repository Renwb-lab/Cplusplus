/*
 * 知识点：power
 * 编译命令：gcc power.cpp -o power.o -lstdc++
 *
 */ 

#include <stdio.h>
#include <stdlib.h>

float power(float x, int y) {
    bool flag = false;
    if (y < 0) {
	y = -y;
	flag = true;	
    }

    float result = 1.0;
    while (y) {
	if (y & 0x01)
	    result *= x;
        y >>= 1;
        x *= x;
    }
    return flag ? 1 / result : result;
}

int main(int argc, char* argv[]) {
    float x = 2.0;
    int y = 10;
    if (argc == 3) {
        sscanf(argv[1], "%f", &x);
        sscanf(argv[2], "%d", &y);
    }
    printf("%d, %lf %d %lf\n", argc,  x, y, power(x, y));
}
