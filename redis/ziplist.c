
/*
 * 压缩列表
 *
 */ 

typedef struct ziplist {
    // 压缩列表占用的内存字节数
    uint32_t zlbytes;

    // 尾节点到起始地址的字节数
    uint64_t zltail;

    // 节点数量
    uint16_t zllen;

    // 节点
    vecort<entry> entryX;

    // 尾端
    uint8_t zlend;

} ziplist;

typedef struct entry {
   // 压缩列表中前一个节点的长度
   // 如果前一节点的长度小于 254 字节， 那么 previous_entry_length 属性的长度为 1 字节： 前一节点的长度就保存在这一个字节里面。
   // 如果前一节点的长度大于等于 254 字节， 那么 previous_entry_length 属性的长度为 5 字节： 其中属性的第一字节会被设置为 0xFE （十进制值 254）， 而之后的四个字节则用于保存前一节点的长度。
   uint8_t previous_entry_length; // < 254
   (uint8_t flag (oxFE); uint32_t previous_entry_length;) >= 254

    //节点的 content 属性所保存数据的类型以及长度
    // encoding
    // 一字节、两字节或者五字节长， 值的最高位为 00 、 01 或者 10 的是字节数组编码： 这种编码表示节点的 content 属性保存着字节数组， 数组的长度由编码除去最高两位之后的其他位记录；
    // 一字节长， 值的最高位以 11 开头的是整数编码： 这种编码表示节点的 content 属性保存着整数值， 整数值的类型和长度由编码除去最高两位之后的其他位记录；
    // 映射关系
    //编码	编码长度	content 属性保存的值
    //00bbbbbb	1 字节	长度小于等于 63 字节的字节数组。
    //01bbbbbb xxxxxxxx	2 字节	长度小于等于 16383 字节的字节数组。
    //10______ aaaaaaaa bbbbbbbb cccccccc dddddddd	5 字节	长度小于等于 4294967295 的字节数组。
    //编码	编码长度	content 属性保存的值
    //11000000	1 字节	int16_t 类型的整数。
    //11010000	1 字节	int32_t 类型的整数。
    //11100000	1 字节	int64_t 类型的整数。
    //11110000	1 字节	24 位有符号整数。
    //11111110	1 字节	8 位有符号整数。
    //1111xxxx	1 字节	使用这一编码的节点没有相应的 content 属性， 因为编码本身的 xxxx 四个位已经保存了一个介于 0 和 12 之间的值， 所以它无须 content 属性。
    // b 、 x 等变量则代表实际的二进制数据


    // 连锁反应, previous_entry_length 可变导致连锁反应
    // 1. 新增一个较长的entry，导致后续的previous_entry_length变成5字节，导致整体长度大约254， 引发后续的变动。
    // 2. 删除后一个小节点后，因该节点前的节点长度较长，引发后续的节点连锁扩张。
    
    // 概率低
    // 1. 首先， 压缩列表里要恰好有多个连续的、长度介于 250 字节至 253 字节之间的节点， 连锁更新才有可能被引发， 在实际中， 这种情况并不多见；
    // 2. 其次， 即使出现连锁更新， 但只要被更新的节点数量不多， 就不会对性能造成任何影响： 比如说， 对三五个节点进行连锁更新是绝对不会影响性能的；
} entry;