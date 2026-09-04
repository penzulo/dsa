# Contains Duplicate

## Core Idea
* **Hash Set Lookup:** Maintain a set of elements seen so far. For each element, check if it already exists in the set before inserting.
* **Early Exit:** Return `true` as soon as a duplicate is found, avoiding unnecessary iteration.
* **Simpler Than Map:** We only need to track existence, not frequency, so a set suffices over a map.

## Resource Stats

| Resource | Complexity | Justification |
| -------- | ---------- | ------------- |
| Time     | `O(n)`     | Single pass through the array with O(1) set lookups |
| Space    | `O(n)`     | Set can grow up to n elements in the worst case |

## More Approaches
Sorting the array first and checking adjacent elements gives `O(n log n)` time with `O(1)` space (if in-place sort is allowed). The brute force nested loop approach is `O(n^2)`.
