#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class cmp
{
public:
  bool operator() (const int& lhs, const int&rhs) const
  {
    return lhs < rhs;
  }
};

int main()
{
    priority_queue<int, vector<int>, cmp> pq;
    pq.push(2);
    pq.push(1);
    pq.push(3);
    while(!pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
    }
    return 1;
}