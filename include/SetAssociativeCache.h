//
// Created by Reggie W. Meeks II on 6/1/26.
//

#ifndef CACHE_ALLOCATOR_SETASSOCIATIVECACHE_H
#define CACHE_ALLOCATOR_SETASSOCIATIVECACHE_H
#include "Cache.h"

enum Policy { FIFO, LRU };

class SetAssociativeCache {
private:
    int numSets;
    int numWays;
    std::vector<std::vector<CacheLine>> sets;
    int hits;
    int misses;
    std::vector<int> fifoCounters;
    int clock;
    Policy policy;
public:
    SetAssociativeCache(int numSets, int numWays, Policy policy);
    void access(int address);
    int getHits();
    int getMisses();
};


#endif //CACHE_ALLOCATOR_SETASSOCIATIVECACHE_H
