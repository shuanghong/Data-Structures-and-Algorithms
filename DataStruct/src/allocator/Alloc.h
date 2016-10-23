#ifndef _ALLOC_H_
#define _ALLOC_H_

#include<cstdint>
#include <iostream>


/*****************************
 * 
 * brief: 空间配置器, 以字节为单位分配
 *
 ****************************/

class myAlloc
{
public:
    static void *allocate(std::size_t bytes);

    static void deallocate(void *ptr, std::size_t bytes);

private:
    static std::size_t roundUp(std::size_t bytes);

    static std::size_t getListIndex(std::size_t bytes);

    static char* allocChunk(std::size_t bytes, uint8_t &nobjs);

    static void* refill(std::size_t bytes);
private:
    static const uint8_t align_ = 8;  //小型区块的上调边界
    static const uint16_t maxbytes_ = 128; // 小型区块的上限，超过的区块由malloc分配
    static const uint8_t num_of_list_ = 16; // free-lists的个数, maxbytes/align
    static const uint8_t num_of_nodes_ = 20; //每次增加的节点数

private:
    static char *start_free;  //内存池起始位置
    static char *end_free;    //内存池结束位置
    static std::size_t heap_size;   //已在堆上分配的空间大小

private:
    /*****************************
     * brief: free-list(空闲链表)的节点结构，用来管理(可用的)内存链表
     * 这里使用 union是为了减少内存的使用， *next 和 data共用一块内存
     * 当使用第一个成员，则指向另一个相同的 obj，而如果使用第二个成员，则指向实际的内存区域
     * 这样就实现了链表节点只使用一个指针大小的空间，却能同时做索引和指向内存区域.
     
            __________________ union obj ___________
            |                                      |
           \|/                                    \|/
            ________________________________________
            |               |                       |
            |   data[1]     |                       |
            |_______________|_______________________|
           /|\
   data_____|    

     *****************************/
    union obj
    {
        union obj *next;
        char data[1];
    };

    /*****************************
     * brief: 16个 free-lists，各自管理大小分别为 8，16，24，32，40，48，56，64，72，80
     * ...128 bytes的内存块
     * 每次配置一大块内存，并维护对应的 free-list, 
     * 下次若再有相同大小的内存需求，就直接从free-list中取出
     *****************************/
    static obj *free_list[num_of_list_];
};

#endif
