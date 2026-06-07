//
// Created by Reggie W. Meeks II on 6/2/26.
//

#include "../include/Cache.h"
#include "../include/SetAssociativeCache.h"
#include "../include/Benchmark.h"
#include "../include/Allocator.h"

#include <chrono>
#include <iostream>


void benchmarkHitRate() {
    Cache directCache(4);
    SetAssociativeCache fifoCache(4, 2, FIFO);
    SetAssociativeCache lruCache(4, 2, LRU);
    for (int i = 0; i < 100000; i++) {
        int addresses[] = {0, 4, 0, 8};
        int address = addresses[i % 4];
        directCache.access(address);
        fifoCache.access(address);
        lruCache.access(address);
    }
    std::cout << "=== Direct-Mapped Cache ===" << std::endl;
    std::cout << "Hits: " << directCache.getHits() << std::endl;
    std::cout << "Misses: " << directCache.getMisses() << std::endl;
    std::cout << "\n=== Set-Associative Cache (FIFO) ===" << std::endl;
    std::cout << "Hits: " << fifoCache.getHits() << std::endl;
    std::cout << "Misses: " << fifoCache.getMisses() << std::endl;
    std::cout << "\n=== Set-Associative Cache (LRU) ===" << std::endl;
    std::cout << "Hits: " << lruCache.getHits() << std::endl;
    std::cout << "Misses: " << lruCache.getMisses() << std::endl;
}

void benchmarkLatency() {
    Cache directCache(4);
    auto dCStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        int address = (i % 65) * 4;
        directCache.access(address);
    }
    auto dCEnd = std::chrono::high_resolution_clock::now();
    auto dCDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(dCEnd - dCStart).count();
    std::cout << "\n=== Direct Cache Duration ===" << std::endl;
    std::cout << dCDuration << " ns" << std::endl;
    std::cout << "Avg per access: " << dCDuration / 100000 << " ns" << std::endl;

    SetAssociativeCache fifoCache(4, 64, FIFO);
    auto fifoCStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        int address = (i % 65) * 4;
        fifoCache.access(address);
    }
    auto fifoCEnd = std::chrono::high_resolution_clock::now();
    auto fifoCDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(fifoCEnd - fifoCStart).count();
    std::cout << "\n=== FIFO Cache Duration ===" << std::endl;
    std::cout << fifoCDuration << " ns" << std::endl;
    std::cout << "Avg per access: " << fifoCDuration / 100000 << " ns" << std::endl;

    SetAssociativeCache lruCache(4, 64, LRU);
    auto lruCStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        int address = (i % 65) * 4;
        lruCache.access(address);
    }
    auto lruCEnd = std::chrono::high_resolution_clock::now();
    auto lruCDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(lruCEnd - lruCStart).count();
    std::cout << "\n=== LRU Cache Duration ===" << std::endl;
    std::cout << lruCDuration << " ns" << std::endl;
    std::cout << "Avg per access: " << lruCDuration / 100000 << " ns" << std::endl;
}

void benchmarkAllocator() {
    Allocator allocator(64, 1024);
    std::vector<void*> pointers;
    auto allocStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1024; i++) {
        pointers.push_back(allocator.allocate());
    }
    auto allocEnd = std::chrono::high_resolution_clock::now();
    auto allocDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(allocEnd - allocStart).count();
    std::cout << "\n=== Allocation Duration ===" << std::endl;
    std::cout << allocDuration << " ns" << std::endl;
    std::cout << "Avg per access: " << allocDuration / 1024 << " ns" << std::endl;

    auto deallocStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1024; i++) {
        allocator.deallocate(pointers.back());
        pointers.pop_back();
    }
    auto deallocEnd = std::chrono::high_resolution_clock::now();
    auto deallocDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(deallocEnd - deallocStart).count();
    std::cout << "\n=== Deallocation Duration ===" << std::endl;
    std::cout << deallocDuration << " ns" << std::endl;
    std::cout << "Avg per access: " << deallocDuration / 1024 << " ns" << std::endl;
}



