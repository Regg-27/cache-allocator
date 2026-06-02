# Learning Log

## Progress
Day 1: project setup, C++ orientation, direct-mapped cache implementation
Day 2: set-associative cache with FIFO and LRU eviction policies
Day 3: 

---

## Day 1
### What I built
Set up CLion and a new C++ project with CMake. Learned the basic differences
between C++ and Java — header vs implementation files, include guards, structs,
and std:: namespace. Built a direct-mapped Cache class with a CacheLine struct,
hit/miss tracking, and an access method that maps addresses to cache lines using
modulo. Verified correct behavior including conflict misses in main.cpp.

### What confused me
CMake build configuration — CLion had two run configurations and was compiling
only main.cpp instead of the full project. Also adjusting to C++ syntax after
only knowing Java.

### How I resolved it
Switched the run configuration to cache_allocator (the CMake target) instead
of main.cpp. Translated Java intuition to C++ by thinking through logic in
Java pseudocode first, then converting.

### Performance notes
N/A — no benchmarking yet. Performance comparisons begin once set-associative
cache and eviction policies are implemented.

---

## Day 2
### What I built
Built a SetAssociativeCache class in C++ with configurable sets and ways.
Implemented two eviction policies — FIFO (First In First Out) using a cycling
counter per set, and LRU (Least Recently Used) using a clock-based timestamp
system. Tested both policies against the same access pattern and confirmed LRU
outperforms FIFO by keeping recently accessed addresses in cache longer.

### What confused me
- Understanding that eviction is a per-set problem, not a per-cache problem. My first instinct was to view the cache like a flat list but now it is more 2-dimensional, like a grid. 

### How I resolved it
- I took a deeper dive into cache structure, recalling my time in CS3650 Computer Architecture and viewed visuals of cache structure. 

### Performance notes
N/A — no formal benchmarking yet. Correctness verified by comparing FIFO vs
LRU on identical access patterns: FIFO produced 1 hit / 4 misses, LRU produced
2 hits / 3 misses on the same sequence. Benchmarking begins Day 3.

---

## Day 3
### What I built


### What confused me


### How I resolved it


### Performance notes