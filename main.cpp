#include <iostream>

#include "include/Cache.h"

int main() {
    std::cout << "Cache Allocator Project" << std::endl;

    Cache cache(4);
    cache.access(8);
    cache.access(16);
    cache.access(8);

    std::cout << "Misses: " << cache.getMisses() << "\nHits: " << cache.getHits() << std::endl;
    return 0;
}
