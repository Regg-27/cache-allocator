//
// Created by Reggie W. Meeks II on 5/31/26.
//

#include "../include/Cache.h"

Cache::Cache(int numLines) {
    this->numLines = numLines;
    this->lines = std::vector<CacheLine>(numLines, {0, false});
    this->hits = 0;
    this->misses = 0;
}

void Cache::access(int address) {
    int index = address % numLines;
    if (lines[index].valid == true && lines[index].tag == address) {
        hits++;
    } else {
        lines[index].valid = true;
        lines[index].tag = address;
        misses++;
    }
}

int Cache::getHits() {
    return hits;
}
int Cache::getMisses() {
    return misses;
}
