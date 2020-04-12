
/*
 * 跳跃表
 *
 */ 

typedef struct zskiplistNode {
    //后退指针
    struct zskiplistNode *backward;

    //分值
    double score;

    //成员对象
    robj *obj;

    //层
    struct zskiplistLevel {
        
        // 前进指针
        struct zskiplistNode *forward;

        // 跨度
        unsigned int span;

    } level[];

} zskiplistNode; 

// 1. 基础节点之间是有序的。
// 2. 为查找方便，使用索引对链表中的节点进行记录。
// 3. 插入时，按照一定的概率将该节点作为索引。
// 4. 删除时，如果索引层只有一个节点的话，则删除给节点。

 typedef struct zskiplist {
    
    // 表头节点和表尾节点
    struct zskiplistNode *header, *tail;

    // 表中节点的数据
    unsigned long length;

    // 表中层数最大节点的层数
    int level;

 };


