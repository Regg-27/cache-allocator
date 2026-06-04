//
// Created by Reggie W. Meeks II on 6/4/26.
//

#include "../include/Allocator.h"

Allocator::Allocator(int blockSize, int numBlocks) {
    this->buffer = std::vector<std::byte>(numBlocks * blockSize);
    this->freeList = std::vector<void*>();
    for (int i = 0; i < numBlocks; i++) {
            freeList.push_back(buffer.data() + (i * blockSize));
    }
    this->blockSize = blockSize;
    this->numBlocks = numBlocks;
}

void* Allocator::allocate() {
    if (freeList.empty()) {
        return nullptr;
    }
    void* block = freeList.back();
    freeList.pop_back();
    return block;
}

void Allocator::deallocate(void* block) {
    if (block == nullptr) {
        return;
    }
    freeList.push_back(block);
}

int Allocator::getFreeListSize() {
    return freeList.size();
}
