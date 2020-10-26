#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

const double epison = 0.00000001L;

bool check(double val, double num) {
    if (fabs(val - num) < epison) {
        return true;
    }
    return false;
}

double func(double num) {
    double begin = 0.0, end = num * 1.0;
    while (true) {
        double mid = (begin + end) / 2.0;
        double val = mid * mid;

        if (check(val, num)) {
            return mid;
        }
        else if (val - num >= epison) {
            end = mid;
        }
        else {
            begin = mid;
        }
    }
    return -1;

}

void test() {
    int i = 0;
    int arr[3] = {0};
    for (; i <= 3; ++i) {
        arr[i] = 0;
        cout << "ok" << endl;
    }
}
int main() {
    cout << func(2.0) << endl;
    test();
    return 0;
}
