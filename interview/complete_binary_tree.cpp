
/*
 * 知识点：完全二叉树，计算三个节点的最近祖先
 * 编译命令：gcc complete_binary_tree.cpp -o complete_binary_tree.o -std=c++11 -lstdc++
 *
 */ 


#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;


void find_ancestors(int n, int root, int x, vector<int> &ancs) {
    int layer = n - 2;
    while (root != x && layer >= 0) {
        ancs.push_back(root);
        int num = pow(2, layer);
        if (root > x) {
            root -= num;
        } else {
            root += num;
        }
        layer -= 1;
    }
    if (root != x) {
        ancs.clear();
    } else {
        ancs.push_back(root);
    }
}

// n 是完全二叉树的层数， 二叉树的值为 1,2, 3, ....
// x, y, z 是三个节点
// 查找 x, y, z 三个节点的最近祖先
int find_common_mininest_ancestor(int n, int x, int y, int z) {
    int max = pow(2, n) - 1;
    vector<int> x_ancs;
    vector<int> y_ancs; 
    vector<int> z_ancs;
    find_ancestors(n, max / 2 + 1, x, x_ancs);
    find_ancestors(n, max / 2 + 1, y, y_ancs);
    find_ancestors(n, max / 2 + 1, z, z_ancs);

    int num = -1;
    int xl = x_ancs.size();
    int yl = y_ancs.size();
    int zl = z_ancs.size();
    for (int i = 0; i < n; ++i) {
        if (xl <= i || yl <= i || zl <= i)
            return num;
        if (x_ancs[i] == y_ancs[i] && x_ancs[i] == z_ancs[i])
            num = x_ancs[i];
        else {
            return num;
        }
    }
    return num;
}

int main(int argc, char* argv[]) {
    int n = 4, x = 5, y = 10, z = 13;
    if (argc == 5) {
        n = stoi(argv[1]);
        x = stoi(argv[2]);
        y = stoi(argv[3]);
        z = stoi(argv[4]);
    }
    int r = find_common_mininest_ancestor(n, x, y, z);
    printf("n: %d, x: %d, y: %d, z: %d -> res: %d\n", n, x, y, z, r);
}
