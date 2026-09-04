# Top K Frequent Elements

## Core Idea
* **Frequency Map:** Count occurrences of each element using a hash map.
* **Min-Heap of Size k:** Maintain a min-heap with at most k elements. For each frequency pair, push it and pop if the heap exceeds size k. This keeps only the k most frequent elements.
* **Extract Results:** Drain the heap to get the top k frequent elements.

## Resource Stats

| Resource | Complexity | Justification |
| -------- | ---------- | ------------- |
| Time     | `O(n log k)` | Building the map is O(n); each of n insertions into the k-size heap costs O(log k) |
| Space    | `O(n)`     | Hash map stores all n elements; heap stores up to k |

## More Approaches
Bucket sort achieves `O(n)` time by grouping elements by frequency and iterating from highest bucket downward. Quickselect can also solve this in `O(n)` average time but has worse worst-case performance.
