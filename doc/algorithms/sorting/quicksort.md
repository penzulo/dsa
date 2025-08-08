# Quick Sort: A Highly Efficient Sorting Algorithm

Quick Sort is a highly efficient **"divide and conquer"** sorting algorithm. The core idea is to recursively break a large array into smaller sub-arrays and sort them.

---

## 🔑 The Three Steps of Quick Sort

The entire algorithm is based on these three steps, performed recursively:

1. **Pivot Selection:**
   Choose an element from the array to be the pivot. This is the element we'll use to partition the array. A good choice is often the middle element.

2. **Partitioning:**
   Rearrange the array so that all elements smaller than the pivot are moved to its left, and all elements larger than the pivot are moved to its right. The pivot is then in its final, sorted position.

3. **Recursion:**
   Recursively apply the Quick Sort algorithm to the sub-array of elements to the left of the pivot and the sub-array of elements to the right of the pivot.

> The recursion stops when a sub-array contains only one element or is empty, as these are already sorted by definition.

---

## The Partitioning Process

Partitioning is the most crucial part of Quick Sort. It's done efficiently using a two-pointer approach:

- We start with two pointers, `i` at the beginning of the sub-array and `j` at the end.
- The **i** pointer moves forward, looking for an element that's greater than or equal to the pivot.
- The **j** pointer moves backward, looking for an element that's less than or equal to the pivot.
- When both pointers stop, **swap** the elements they're pointing to. This moves both elements to a more correct position relative to the pivot.
- The pointers then continue moving inward.
- The process stops when the **i** and **j** pointers cross. The **i** pointer's final position marks the boundary between the two new sub-arrays.

The partition function returns the final position of the pivot (which is the final position of the `i` pointer).

---

## Time and Space Complexity

- **Worst-Case Time Complexity:** `O(n^2)` 😥
  This happens when the pivot is consistently the smallest or largest element in the array, leading to very unbalanced partitions where one sub-array is empty and the other contains almost all elements.

- **Average-Case Time Complexity:** `O(n log n)` 😎
  This is Quick Sort's typical performance. It occurs when the pivot selection leads to balanced partitions, where the array is roughly halved at each step.

- **Best-Case Time Complexity:** `O(n log n)`
  Similar to the average case, this happens with perfectly balanced partitions.

- **Space Complexity:** `O(log n)` (in-place)
  Quick Sort is an **"in-place"** algorithm, meaning it doesn't require a large amount of extra memory. The space complexity is determined by the depth of the recursive call stack, which is `O(log n)` in the average case and `O(n)` in the worst case (unbalanced partitions).
