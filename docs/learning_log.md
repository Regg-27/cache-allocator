# Learning Log

## Progress
Day 1: project setup, C++ orientation, direct-mapped cache implementation

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