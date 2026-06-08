# Cache Allocator
A CPU cache simulator and fixed-size memory allocator built from scratch in C++,
with hit rate and latency benchmarks and Python visualizations.

## Overview
This project simulates CPU cache behavior and implements a custom memory allocator
in C++. The cache simulator models three configurations — direct-mapped, FIFO
set-associative, and LRU set-associative — and measures hit rates and access
latency across all three. The memory allocator manages a raw byte buffer divided
into fixed-size blocks, using a free list to track available memory. Benchmarks
on 100,000 accesses show LRU achieving a ~50% hit rate compared to 0% for
direct-mapped on a conflict-heavy access pattern, and LRU costing ~78x more
per access than direct-mapped under constant eviction pressure.

## Motivation
In my Computer Architecture course (CS3650) we spent most of our time on the
math behind cache behavior — hit rates, miss penalties, access patterns — but
never translated any of it into working code. I wanted to close that gap. What
actually makes a cache fast? How does eviction policy affect real performance
numbers, not just theoretical ones?

The memory allocator grew out of the same question. Once you understand how a
cache manages memory access patterns, the natural next question is how memory
itself gets managed underneath. Building both in the same project let me see
how they connect — cache behavior is shaped by allocation patterns, and
allocation patterns are shaped by how memory is laid out. You can't fully
understand one without the other.

## Architecture & Design

### Architectural Style
This project follows a component-based architecture where the cache simulator
and memory allocator are independent systems that share a common data model.
The cache simulator separates the direct-mapped implementation (Cache) from
the set-associative implementation (SetAssociativeCache), with eviction policy
controlled by a Policy enum at construction time rather than through subclassing.
The memory allocator uses a free list pattern — a vector of void* pointers to
available blocks — that mirrors how real allocators like tcmalloc manage memory
pools. Benchmarking and visualization are handled by a standalone Benchmark
module and a Python script, keeping measurement concerns separate from
implementation.

### Package Structure
```
cache-allocator/
├── docs/
│   ├── learning_log.md
│   └── README.md
├── include/
│   ├── Allocator.h          # fixed-size block allocator interface
│   ├── Benchmark.h          # benchmark function declarations
│   ├── Cache.h              # direct-mapped cache + CacheLine struct
│   └── SetAssociativeCache.h # set-associative cache with FIFO/LRU policy
├── scripts/
│   └── visualize.py         # matplotlib hit rate and latency charts
├── src/
│   ├── Allocator.cpp        # free list allocator implementation
│   ├── Benchmark.cpp        # hit rate, latency, and allocator benchmarks
│   ├── Cache.cpp            # direct-mapped cache implementation
│   └── SetAssociativeCache.cpp # set-associative cache implementation
├── CMakeLists.txt
└── main.cpp                 # correctness tests and benchmark entry point
```

### Key Design Decisions
- **Policy enum over subclassing:** FIFO and LRU eviction are controlled by a
  Policy enum passed at construction time. This keeps both policies in one class
  rather than creating a class hierarchy for what is ultimately a single behavioral
  difference.
- **Separate hit rate and latency benchmarks:** Hit rate uses 2 ways to force
  eviction and reveal policy differences. Latency uses 64 ways to amplify LRU's
  scan overhead. Different configurations, different stories — noted in the README.
- **void* free list:** The allocator tracks available blocks as raw memory
  addresses rather than typed objects. This matches how real allocators work and
  avoids the overhead of wrapping each block in a typed container.
- **CacheLine as a shared struct:** Both Cache and SetAssociativeCache use the
  same CacheLine struct defined in Cache.h. Shared data model, no duplication.
- **Python visualization as embedded tooling:** Benchmark results are hardcoded
  into visualize.py and regenerated when numbers change. Keeps visualization
  lightweight without adding a runtime dependency to the C++ project.

### Known Limitations
- Eviction policies are only implemented in SetAssociativeCache — direct-mapped
  cache has no eviction policy choice since each address maps to exactly one line.
- The memory allocator only supports fixed-size blocks — variable-size allocation
  would require a more complex free list with size metadata per block.
- Benchmark numbers are hardcoded in visualize.py and must be manually updated
  when re-run on different hardware.
- No thread safety — concurrent access to the cache or allocator from multiple
  threads would produce undefined behavior.

## Benchmark Results

### Cache Hit Rate (4 sets, 2 ways, 100,000 accesses, pattern: 0,4,0,8)
| Cache Type    | Hits   | Misses  | Hit Rate |
|---------------|--------|---------|----------|
| Direct-Mapped | 0      | 100,000 | 0%       |
| FIFO          | 25,000 | 75,000  | 25%      |
| LRU           | 49,999 | 50,001  | ~50%     |

### Cache Latency (4 sets, 64 ways, 100,000 accesses, constant eviction)
| Cache Type    | Total Time  | Avg per Access |
|---------------|-------------|----------------|
| Direct-Mapped | ~929,958ns  | ~9ns           |
| FIFO          | ~49,662,208ns | ~496ns       |
| LRU           | ~70,313,292ns | ~703ns       |

### Allocator Performance (1024 blocks, 64 bytes each)
| Operation     | Total Time | Avg per Operation |
|---------------|------------|-------------------|
| Allocate      | ~26,125ns  | ~25ns             |
| Deallocate    | ~20,875ns  | ~20ns             |

## How to Run
**Prerequisites:** C++17, CMake 4.2+, Python 3.9+, matplotlib, numpy

```bash
# Clone the repo
git clone https://github.com/Regg-27/cache-allocator.git
cd cache-allocator

# Build and run
cmake -B cmake-build-debug
cmake --build cmake-build-debug
./cmake-build-debug/cache_allocator

# Run Python visualization
pip3 install matplotlib numpy
python3 scripts/visualize.py
```

## What I Learned
Before this project, a cache was a black box — fast memory that lived somewhere
between the CPU and RAM. Now I understand the tradeoffs underneath: direct-mapped
is simple and fast but fails completely on conflicting addresses, FIFO recovers
some performance but evicts blindly, and LRU doubles FIFO's hit rate by rewarding
recency. The benchmark numbers made those tradeoffs real in a way that Computer
Architecture lectures didn't — seeing LRU achieve 50% hit rate while direct-mapped
hit 0% on the same access pattern is a different kind of understanding than
solving a formula on paper.

The memory allocator added a second layer to that intuition. Allocation isn't
free — every allocate() and deallocate() call has measurable cost, and the free
list pattern shows why fixed-size allocators are so fast: no searching, no
coalescing, just a push or pop on a stack of pointers.

Building this in C++ also broke a mental barrier. Coming in with zero C++
experience, I expected it to feel foreign. Instead, the Java foundation translated
almost directly — the logic is the same, the control is just lower. The project
confirmed something I'd heard but hadn't felt: if you know one language well,
the next one is mostly syntax.

## Future Features
- Variable-size block allocator with size metadata and coalescing of adjacent
  free blocks
- Fully associative cache implementation for comparison
- Write-back and write-through cache policies
- Multi-threaded benchmark to test allocator under concurrent access
- Export benchmark results from C++ directly to CSV for automatic visualization
  without hardcoding numbers
