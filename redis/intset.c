
/*
 * 整数集合
 *
 */ 


typedef struct intset {
    
    //编码方式，决定 contents 中的存储类型
    // INTSET_ENC_INT16 -> int8_t [-32768, 32767]
    // INTSET_ENC_INT32 -> int32_t [-214748348, 2,147,483,64]
    // INTSET_ENC_INT64 -> int64_t [-9,223,372,036,854,775,808, 9,223,372,036,854,775,807]
    uint32_t encoding;
    // 升级
    // 1. 提升灵活性， 一个类型中可以存放三种不同的类型。
    // 2. 节约内存， 只在必要时进行升级，相对于使用最大空间存放不同类型而言。
    // 降级
    // 1. 降级不更改encoding类型

    // 集合中包含的元素数量
    uint32_t length;

    // 保存元素的数据, 有序，无重复
    int8_t contents[];

} intset;

