
/*
 * 知识点：循环打印数组，不借助与二维数组
 * 编译命令：gcc group2.cpp -o group2.o -std=c++11 -lstdc++
 *
 */ 

#include <vector>
#include <iostream>

using namespace std;

int get_ring_id(int x, int y, int n) {
    // get ring id
    // min = min(x, y)
    // max = max(x, y)
    // return min(min, n - 1 - max)
    if (x > y) {
        int t = x;
        x = y;
        y = t;
     } 
     int t = n - 1 - y;
     return (x <= t) ? x : t;
}

void print_cycle_arr(int n) {
    
    int ids = (n & 0x01) ? (n + 1) / 2 : n / 2;
    vector<int> arr(ids + 1, 0);
    for (int id = 1; id < ids; ++id) {
        // (n - (id - 1) * 2) is the length of the lastest layer.
        // 4 * (n - (id - 1) * 2) - 4 is the number of the lastest layer.
        arr[id] = arr[id - 1] + 4 * (n - (id - 1) * 2) - 4; 
    }
    
    for(int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            int id = get_ring_id(x, y, n);
            //printf("(%d, %d) -> %d\n", x, y, id);
            int t = arr[id];
            if (x == id) {
                // top
                t += (y + 1 - id);
                // note: we need know the nubmer relative the ring, so there is minus id
            }
            else if (y == n - 1 - id) {
                // top
                t += (n - id * 2);
                // right
                t += (x - id);
            }
            else if (x == n - 1 - id) {
                // top
                t += (n - id * 2);
                // right
                t += (n - id * 2 - 1);
                // bottom
                t += (n - 1 - id - y);
            }
            else if (y == id) {
                // top
                t += (n - id * 2);
                // right
                t += (n - id * 2 - 1);
                // bottom
                t += (n - id * 2 - 1);
                // left
                t += (n - 1 - id - x);
            }
            printf("%3d ", t);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    print_cycle_arr(5);
}
