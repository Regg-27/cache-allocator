//
// Created by Reggie W. Meeks II on 6/4/26.
//

#ifndef CACHE_ALLOCATOR_ALLOCATOR_H
#define CACHE_ALLOCATOR_ALLOCATOR_H
#include <vector>

class Allocator {
private:
    std::vector<std::byte> buffer;
    std::vector<void*> freeList;
    int blockSize;
    int numBlocks;
public:
    Allocator(int blockSize, int numBlocks);
    void* allocate();
    void deallocate(void* block);
    int getFreeListSize();
    int getAllocatedCount();
    double getUtilization();
};



#endif //CACHE_ALLOCATOR_ALLOCATOR_H
