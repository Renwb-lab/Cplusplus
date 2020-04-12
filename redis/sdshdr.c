
/*
 * 简单动态字符串
 *
 */

struct sdshdr {
    // 记录buf数组中已使用字节的数量
    int len;

    // 记录buf数组中未使用字节的数量
    int free;

    //字节数组，用于保存字符串
    char buf[];

    //字符串长度
    int size() const {
        return len;
    }

    //空间预分配.
    //小于1M的数量，分配额外相同的大小。
    //大于等于1M的数量，分配额外1M
    void sdscat(char buf[]);
    
    //惰性空间释放
    //释放空间时，把释放的空间加到free字段上。
    void sdstrim(char buf[]);

    //二进制安全
};

