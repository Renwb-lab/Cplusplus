#include <iostream>

using namespace std;

void removeDuplicates(char str[]) {

    if (str == NULL)
        return;

    int len = strlen(str);
    if (len < 2)
        return;

    bool hit[256];
    memset(hit, false, 256);
    hit[str[0]] = true;
    int tail = 1;
    for (int i = 1; i < len; ++i) {
        if (!hit[str[i]]) {
            str[tail++] = str[i];
            hit[str[i]] = 1;
        }
    }
    str[tail] = 0;
}

int main(int argc, char *argv[]) {
    cout << removeDuplicates()
    return 0;
}
