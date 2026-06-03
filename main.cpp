#include <iostream>
#include "include/Cache.h"
#include "include/SetAssociativeCache.h"
#include "include/Benchmark.h"

int main() {
    // // Test 1: Direct-mapped conflict miss
    // std::cout << "=== Direct-Mapped Cache ===" << std::endl;
    // Cache directCache(4);
    // directCache.access(8);
    // directCache.access(16);
    // directCache.access(8);
    // std::cout << "Hits: " << directCache.getHits() << std::endl;
    // std::cout << "Misses: " << directCache.getMisses() << std::endl;
    //
    // // Test 2: FIFO eviction
    // std::cout << "\n=== Set-Associative Cache (FIFO) ===" << std::endl;
    // SetAssociativeCache fifoCache(4, 2, FIFO);
    // fifoCache.access(0);   // miss, loads into way 0
    // fifoCache.access(4);   // miss, loads into way 1
    // fifoCache.access(0);   // hit
    // fifoCache.access(8);   // miss, evicts way 0 (FIFO) - evicts 0
    // fifoCache.access(0);   // miss - 0 was evicted
    // std::cout << "Hits: " << fifoCache.getHits() << std::endl;
    // std::cout << "Misses: " << fifoCache.getMisses() << std::endl;
    //
    // // Test 3: LRU eviction - same pattern, different result
    // std::cout << "\n=== Set-Associative Cache (LRU) ===" << std::endl;
    // SetAssociativeCache lruCache(4, 2, LRU);
    // lruCache.access(0);   // miss, loads into way 0
    // lruCache.access(4);   // miss, loads into way 1
    // lruCache.access(0);   // hit - updates 0's timestamp, 4 is now LRU
    // lruCache.access(8);   // miss, evicts 4 (LRU) not 0
    // lruCache.access(0);   // hit - 0 is still in cache
    // std::cout << "Hits: " << lruCache.getHits() << std::endl;
    // std::cout << "Misses: " << lruCache.getMisses() << std::endl;

    benchmarkHitRate();
    benchmarkLatency();

    return 0;
}
