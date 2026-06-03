cmake_minimum_required(VERSION 4.2)
project(cache_allocator)

set(CMAKE_CXX_STANDARD 17)

add_executable(cache_allocator main.cpp
        src/Cache.cpp
        include/cache.h
        include/SetAssociativeCache.h
        src/SetAssociativeCache.cpp
        src/Benchmark.cpp
        include/Benchmark.h)
