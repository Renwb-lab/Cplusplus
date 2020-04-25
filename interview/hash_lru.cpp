
/*
 * 知识点：实现基于hash的lru算法
 * 编译命令：gcc hash_lru.cpp -o hash_lru.o -std=c++11 -lstdc++
 *
 */ 

#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

typedef int KEY_T;
typedef int VAL_T;

struct Node {
    KEY_T key;
    VAL_T value;
    Node (KEY_T key, KEY_T value) : key(key), value(value) {}
};

class HashLRU {

public:
    HashLRU(int threshold=1000000, int hashsize=100): _threshold(threshold), _hashsize(hashsize), _hash(_hashsize) {}

    void insert(KEY_T key, VAL_T value) {
        auto iter = _cache.find(key);
        if (iter == _cache.end()) {
            if (_size >= _threshold) {
                _remove();
            }
            Node n(key, value);
            _add(n);
        }
        else {
            (*(iter->second))->value = value;
            _adjust(key, iter);
        }
    }

    VAL_T get(const KEY_T key) {
        auto iter = _cache.find(key);
        if (iter == _cache.end())
            return -1;
        _adjust(key, iter);
        return (*(iter->second))->value;
    }

    void print() {
        cout << "===================================" << endl;
        for (auto it = _used.begin(); it != _used.end(); ++it) {
            cout << "key: " << it->key << ", value: "  <<  it->value << endl;
        }
        cout << "===================================" << endl;
    }

    void print_hash(int index) {
        cout << "============== " << index << " =================" << endl;
        for(auto it = _hash[index].begin(); it != _hash[index].end(); ++it) {
            cout << "key: " << (*it)->key << " value: " << (*it)->value << endl;
        }
        cout << "===================================" << endl;
    }

private:
    int _threshold;
    int _size;
    int _hashsize;

    typedef list<Node> LN;
    
    typedef LN::iterator ITER;
    typedef list<ITER> LINE;
    typedef vector<LINE> HASH;

    typedef LINE::iterator IITER;
    typedef unordered_map<KEY_T, IITER> UM;

    // list类型，里面存储的Node. 最近更新的结果放在list的前面。
    LN _used;
    // vector类型，里面存放的list, 表示链式存储。list中存储的是_used中节点的迭代器。
    HASH _hash;
    // unoredered_map 类型，key 为Node的key, value 为vector中list的迭代器。
    UM _cache;

private:
    void _add(Node n) {
        _used.push_front(n);
        _hash[n.key % _hashsize].push_front(_used.begin());
        _cache[n.key] = _hash[n.key % _hashsize].begin();
        ++_size;
    }

    void _remove() {
        Node n = _used.back();
        _used.pop_back();

        auto iter = _cache.find(n.key);
        _hash[n.key % _hashsize].erase(iter->second);
        _cache.erase(iter);
       
        --_size;
    }

    void _adjust(KEY_T key, UM::iterator iter) {
        int index = key % _hashsize;
        ITER it = *(iter->second);
        Node n = *(it);

        _used.erase(it);
        _used.push_front(n);

        _hash[index].erase(iter->second);
        _hash[index].push_front(_used.begin());
        _cache[key] = _hash[index].begin();
    }
};

int main(int argc, char* argv[]) {
    HashLRU hash_lru(10, 2);
    for (int i = 0; i <= 10; ++i)
        hash_lru.insert(i, i+1);
    hash_lru.print();

    hash_lru.insert(2, 3);
    hash_lru.insert(3, 4);
    cout << hash_lru.get(2) << endl;
    //hash_lru.print_hash(1);
    hash_lru.print();
    cout << hash_lru.get(1) << endl;
    //hash_lru.print_hash(1);
    hash_lru.print();
    cout << hash_lru.get(3) << endl;
    //hash_lru.print_hash(1);
    hash_lru.print();
    return 0;
}
