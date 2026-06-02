//
// Created by Reggie W. Meeks II on 6/1/26.
//

#include "../include/SetAssociativeCache.h"



SetAssociativeCache::SetAssociativeCache(int numSets, int numWays, Policy policy) {
    this->numSets = numSets;
    this->numWays = numWays;
    this->hits = 0;
    this->misses = 0;
    this->sets = std::vector<std::vector<CacheLine>>(numSets, std::vector<CacheLine>(numWays, {0, false}));
    this->fifoCounters = std::vector<int>(numSets, 0);
    this->clock = 0;
    this->policy = policy;
}

void SetAssociativeCache::access(int address) {
    int index = address % numSets;
    for (int i = 0; i < numWays; i++) {
        if (sets[index][i].valid == true && sets[index][i].tag == address) {
            hits++;
            if (policy == LRU) {
                sets[index][i].lastUsed = clock;
                clock++;
            }
            return;
        }
    }
    for (int i = 0; i < numWays; i++) {
        if (sets[index][i].valid == false) {
            sets[index][i].valid = true;
            sets[index][i].tag = address;
            misses++;
            if (policy == LRU) {
                sets[index][i].lastUsed = clock;
                clock++;
            }
            return;
        }
    }
    if (policy == FIFO) {
        sets[index][fifoCounters[index]].valid = true;
        sets[index][fifoCounters[index]].tag = address;
        fifoCounters[index] = (fifoCounters[index] + 1) % numWays;
        misses++;
    } else {
        int lruIndex = 0;
        for (int i = 1; i < numWays; i++) {
            if (sets[index][i].lastUsed < sets[index][lruIndex].lastUsed) {
                lruIndex = i;
            }
        }
        sets[index][lruIndex].valid = true;
        sets[index][lruIndex].tag = address;
        sets[index][lruIndex].lastUsed = clock;
        clock++;
        misses++;
    }
}

int SetAssociativeCache::getHits() {
    return hits;
}

int SetAssociativeCache::getMisses() {
    return misses;
}
