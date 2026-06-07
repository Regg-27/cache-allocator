import matplotlib.pyplot as plt
import numpy as np


names = ["Direct", "FIFO", "LRU"]
hits = [0, 25000, 49999]
misses = [100000, 75000, 50001]
latency = [9, 496, 703]

x = np.arange(len(names))
width = 0.35

plt.figure()
plt.bar(x - width/2, hits, width, label="Hits")
plt.bar(x + width/2, misses, width, label="Misses")
plt.xticks(x, names)
plt.title("Hit Rate Comparison")
plt.xlabel("Cache Type")
plt.ylabel("Count")
plt.legend()
plt.savefig("hit_rate.png")

plt.figure()
plt.bar(names, latency, color=["blue", "orange", "green"])
plt.title("Average Access Latency")
plt.xlabel("Cache Type")
plt.ylabel("Nanoseconds")
plt.savefig("latency.png")

alloc_ops = ["Allocate", "Deallocate"]
alloc_latency = [25, 20]

plt.figure()
plt.bar(alloc_ops, alloc_latency, color=["blue", "orange"])
plt.title("Allocator Performance")
plt.xlabel("Operation")
plt.ylabel("Avg Nanoseconds per Operation")
plt.savefig("allocator_perf.png")