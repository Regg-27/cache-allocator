//
// Created by Reggie W. Meeks II on 5/31/26.
//

#ifndef CACHE_ALLOCATOR_CACHE_H
#define CACHE_ALLOCATOR_CACHE_H
#include <vector>

struct CacheLine {
    int tag;
    bool valid;
};

class Cache {
private:
    int numLines;
    std::vector<CacheLine> lines;
    int hits;
    int misses;
public:
    Cache(int numLines);
    void access(int address);
    int getHits();
    int getMisses();
};


#endif //CACHE_ALLOCATOR_CACHE_H
