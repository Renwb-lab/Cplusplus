
/*
 * 知识点：实现微信随机分红包
 * 编译命令：gcc chatmonery.cpp -o chatmonery..o -std=c++11 -lstdc++
 *
 */ 

#include <set>
#include <random>
#include <chrono>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void chatmoney(int n, int m, vector<double> &result) {
    
    set<int> s;
    int size = m * 100;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine e(seed);
    uniform_int_distribution<unsigned> u(0, size);
    while (s.size() < m - 1) {
        unsigned rand = u(e);
        if (rand == 0 || rand == size)
            continue;
        s.insert(rand);
    }
    unsigned pre = 0;
    for (auto iter = s.begin(); iter != s.end(); ++iter) {
        double money = (*iter - pre) * 1.0 / size * n;
        result.push_back(money);
        cout << "random: " << *iter << " money: " << money << endl; 
        pre = *iter;
    }
    double money = (size - pre) * 1.0 / size * n;
    result.push_back(money);
}

int main(int argc, char* argv[]) {
    int n = 100;
    int m = 10;
    if (argc == 3) {
        n = stoi(argv[1]);
        m = stoi(argv[2]);
    }

    vector<double> result;
    chatmoney(n, m, result);
    double sum = 0;
    for (int i = 0; i < result.size(); ++i) {
        cout << "id: " << i << " money: " << result[i] << endl;
        sum += result[i];
    }
    cout << "sum: " << sum << endl;
}
