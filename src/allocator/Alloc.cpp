#include "Alloc.h"


char *myAlloc::start_free = nullptr;  
char *myAlloc::end_free = nullptr;    
std::size_t myAlloc::heap_size = 0;   

myAlloc::obj *myAlloc::free_list[num_of_list_] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
};


/*****************************
 * 
 * brief: 空间分配, 从free list上取或者是内存池上取
 *
 ****************************/

void *myAlloc::allocate(std::size_t bytes)
{
    std::size_t index = getListIndex(bytes);    // 所需空间对应的 free list
    std::cout << "allocate() bytes:" << bytes 
              << ","
              << "free list index:" << index 
              << std::endl;

    obj **my_free_list = free_list + index;
    obj *result = *my_free_list;
    if (result == nullptr)   // 当前 free list 已没有空间
    {
        void *list = refill(roundUp(bytes));
        return list;
    } 

    *my_free_list = result->next;     // 调整free list，指向下一个可用的内存空间

    std::cout << "obtain memory from free list, memory address: " << result << std::endl
              << "change free list to next free, memory address: " << *my_free_list << std::endl
              << "chunk byte size: " << (*my_free_list - result) << std::endl;

    return result;
}

/*****************************
 * 
 * brief: 空间回收, 将使用的区块还给free list, 但是并没有还给系统内存
 *
 ****************************/
void myAlloc::deallocate(void *ptr, std::size_t bytes)
{
    if(!ptr)
    {
        std::cout << "deallocate() ptr is null!!!" << std::endl;
        return;
    }

    std::size_t index = getListIndex(bytes);    // 释放空间对应的 free list
    std::cout << "deallocate() bytes:" << bytes 
              << "," 
              << "index:" << index 
              << std::endl;

    obj **my_free_list = free_list + index;
    obj *used_free_list = (obj *)ptr;

    used_free_list->next = *my_free_list;
    *my_free_list = used_free_list;     //空闲链表指向原先使用的区块
}

/*****************************
 * 
 * brief: 根据所需的字节数找到对应的 free-list(0~7)
 * 1~8 bytes --- free_list[0]
 * 9~16 bytes --- free_list[1]
 * 17~24 bytes --- free_list[2]
 *
 ****************************/
std::size_t myAlloc::getListIndex(std::size_t bytes)
{
    return static_cast<std::size_t>((bytes + align_ -1)/align_ -1);
}

/*****************************
 * 
 * brief: 将 bytes上调至 8的倍数, 向上舍入操作
 * 下面的表达式与 ((bytes + align_ -1) * align_)/align_ 等价，但效率更高
 * align_ -1 是实际内存对齐的粒度，如 align_ = 8 时，只需要7就能实际表示8个数(0~7)
 *
 * ~(align_ - 1)就是进行舍入的粒度  
 * (bytes + align_-1)就是先进行进位, 然后截断, 这就保证了是向上舍入的
 * 例如byte = 100, align_ = 8的情况  
 * ~(align_ - 1) = (1 000)B
 * (bytes + align_-1) = (1 101 011)B 
 * ((bytes + align_-1) & ~(align_ - 1)) = (1 101 000 )B = (104)D
 * 104 / 8 = 13, 这就实现了向上舍入 
 * 对于byte刚好满足内存对齐的情况下, 结果保持byte大小不变  
 *
 ****************************/
std::size_t myAlloc::roundUp(std::size_t bytes)
{
    return ((bytes + align_-1) & ~(align_ -1));
}



/*****************************
 * 
 * brief: 从内存池中申请空间给 free list, 如果内存池中也没有空间则申请系统内存
 * 入参：
 * bytes, 单个区块的字节数，已上调至 8 的倍数
 * nobjs, 区块数，默认是20，会根据内存池中的空间容量调整
 *
 ****************************/
char* myAlloc::allocChunk(std::size_t bytes, uint8_t &nobjs)
{
    char *result = nullptr;
    std::size_t total_bytes = bytes * nobjs;    // 申请分配的空间
    std::size_t bytes_left = end_free - start_free; // 内存池中剩余的空间

    std::cout << "allocChunk() bytes from memory pool:" << bytes 
              << "," 
              << "total bytes:" << total_bytes
              << "," 
              << "pool bytes left:"  << bytes_left
              << std::endl;

    if (bytes_left >= total_bytes)  // 内存池中剩余空间满足需要分配的空间 
    {
        result = start_free;        // 已分配的起始地址
        start_free = start_free + total_bytes;  // 更新内存池的起始地址
        return result;
    }
    else if (bytes_left >= bytes)   // 内存池中剩余空间不能满足默认20个区块的空间，但是够分配一个或几个区块的空间
    {
        nobjs = bytes_left / bytes;     // 更新可分配的区块个数
        total_bytes = nobjs * bytes;    // 更新分配的总空间
        result = start_free;
        start_free += total_bytes;      // 新新内存池起始地址
        return result;
    }
    else        // 内存池剩余空间不够一个区块的空间, 从系统内存中申请空间到内存池中
    {
        size_t bytes_to_get = 2 * total_bytes + roundUp(heap_size >> 4);    
        if (bytes_left > 0)                                                 // 但是还有空间，比如要申请的区块是24bytes，内存池中只有8bytes
        {
            obj **my_free_list = free_list + getListIndex(bytes_left);      // 将内存池中的剩余空间加入到对应的空闲链表
            ((obj *)start_free)->next = *my_free_list;
            *my_free_list = (obj *)start_free;                              // 空闲链表始终指向可用的内存
        }
        start_free = (char *)malloc(bytes_to_get);
        if (!start_free)        // 系统内存分配失败，log
        {
            end_free = 0;
            std::cout <<"allocChunk() " << std::cout << "malloc failed!!!" << std::endl;
            return nullptr;
        }

        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;

        return allocChunk(bytes, nobjs);    // 内存池更新完毕，再从内存池中取内存给空闲链表，更新 nobjs
    }
}

/*****************************
 * 
 * brief: 构建空闲链表 free list
 *
 ****************************/
void* myAlloc::refill(std::size_t bytes)
{
    std::cout << "refill() bytes:" << bytes 
              << std::endl;

    uint8_t nobjs = num_of_nodes_;
    obj **my_free_list = nullptr;
    obj *result = nullptr;
    obj *current_obj = nullptr, *next_obj = nullptr;

    char *chunk = allocChunk(bytes, nobjs);
    if (chunk == nullptr)
    {
        std::cout << "refill() failed!!!" << std::endl;
        return nullptr;
    }
        
    if (nobjs == 1)     // 取出的空间只够一个区块使用，返回这个区块，也不需要填充空闲链表了
    {
        return chunk;
    }
    else                // 将取出的多余空间加入到对应的 free_list. 第1个区块返回, 剩下 nobjs-1个由free_list管理
    {
        my_free_list = free_list + getListIndex(bytes);
        result = (obj *)(chunk);
        next_obj = (obj *)(chunk + bytes);
        *my_free_list = next_obj;

        for (int i = 1;; ++i)
        {
            current_obj = next_obj;
            next_obj = (obj *)((char *)next_obj + bytes);
            if (i == nobjs - 1)
            {
                current_obj->next = nullptr;
                break;
            }
            else
            {
                current_obj->next = next_obj;
            }
        }

        auto dumpFreeList = [](obj *free_list)
        {
            std::cout << "dump free list..." << std::endl
                      << "node pointer size: " << sizeof(obj) << std::endl;

            std::cout << "memory address managered by free list: " << std::endl;

            obj *current_node = free_list;
            obj *next_node = nullptr;
            for (int i = 0;; ++i)
            {
                std::cout << current_node << ", " 
                          << "head address: " << current_node->data
                          << std::endl;
                if (current_node->next == nullptr)
                    break;

                next_node = current_node->next;
                current_node = next_node;
            }
        
        };
        dumpFreeList(*my_free_list);

        return result;
    }

}
