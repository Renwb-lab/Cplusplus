
/*
 * 字典
 *
 */ 

typedef struct dictEntry {
    
    // 键
    void *key;

    // 值
    union {
        void *val;
        uint64_t u64;
        int64_t s64;
    } v;

    // 指向下一哈希表节点，形成链表
    struct dictEntry* next;

} dictEntry;

typedef struct dictht {
    
    // 哈希表数组, 二维数组
    dictEntry **table;

    // 哈希表大小
    unsigned long size;

    // 哈希表大小掩码， 用于计算索引值
    // 总是等于 size - 1
    unsigned long sizemask;

    // 该哈希表已有节点的数量
    unsigned long used;

} dictht;

typedef struct dict {
    // 类型特定函数
    dictType *type;

    // 私有数据
    void *privdata;

    // 哈希表
    dictht ht[2];

    // rehash 索引
    // 当rehash 不在进行时，值为-1
    int rehashidx;
} dict;

typedef struct dictType {
    // 计算哈希值的函数
    unsigned int (*hashFunction)(const void *key);

    // 复制键的函数
    void *(*keyDup)(void *privdata, const void *key);

    // 复制值的函数
    void *(*valDup)(void *privdata, const void *obj);

    // 对比键的函数
    int (*keyCompare)(void *privdata, const void *key1, const void *key2);

    // 销毁键的函数
    void (*keyDestructor)(void *privdata, void *key);

    // 销毁值的函数
    void (*valDestructor)(void *privdata, void *obj);
} dictType;


//  使用字典中设置的哈希函数，设置键key的哈希值
hash = dict->type->hashFuction(key)

// 使用哈希表的sizemask属性和哈希值，计算出索引值
// 根据情况不同，ht[x] 可以是ht[0] 或者 ht[1]
index = hash & dict->ht[x].sizemask;


// 负载因子
//  load_factor = ht[0].used / ht[0].size

// rehash
// 1. 扩展： ht[0].used * 2 < x < 2^n
// 1.1 load_factor >= 1 while no (BGSAVE or BGREWRITEAOF)
// 1.2 load_factor >= 5 while BGSAVE or BGREWRITEAOF
// 2. 收储： ht[0].used < x < 2^n
// 2.1 load_factor < 0.1



