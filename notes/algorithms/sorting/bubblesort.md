# Bubble Sort: A Simple Comparison-Based Sorting Algorithm

Bubble Sort is one of the simplest sorting algorithms. It works by repeatedly swapping adjacent elements if they are in the wrong order. Though not efficient for large datasets, it serves well for understanding basic sorting principles.

---

## 🔑 How Bubble Sort Works

The algorithm is based on two key ideas:

1. **Passes:**
   Bubble Sort performs multiple passes over the array. In each pass, it compares each pair of adjacent items and swaps them if they’re in the wrong order (for ascending sort, swaps when the left item is bigger).

2. **Swapping:**
   After each pass, the largest unsorted element "bubbles up" to its correct position at the end of the array.

> The process repeats until no swaps are needed in a pass, indicating that the array is sorted.

---

## Bubble Sort: Step-by-Step

- Begin at the start of the array.
- Compare the first pair of adjacent elements. If out of order, swap them.
- Continue comparing and swapping adjacent elements throughout the array.
- After each pass, the largest unsorted value is in its correct place.
- Reduce the number of elements to check by 1 (since the end is now sorted).
- Repeat until the array is fully sorted.

---

## Time and Space Complexity

- **Worst-Case Time Complexity:** `O(n^2)` 😥
  Occurs when the array is reverse sorted. Each pair is compared in every pass.

- **Best-Case Time Complexity:** `O(n)` (optimized version) 😄
  If the array is already sorted, only one pass is needed (using a flag to detect no swaps).

- **Average-Case Time Complexity:** `O(n^2)`
  Like the worst case, since all pairs are compared on average.

- **Space Complexity:** `O(1)` (in-place)
  Bubble Sort sorts the array without requiring extra storage.

---

## Example

Original Array: `[5, 3, 8, 4, 2]`

First Pass:
- Compare 5 & 3: Swap → `[3, 5, 8, 4, 2]`
- Compare 5 & 8: No swap
- Compare 8 & 4: Swap → `[3, 5, 4, 8, 2]`
- Compare 8 & 2: Swap → `[3, 5, 4, 2, 8]`

After first pass, 8 is in the correct position. Repeat for remaining elements.

---

## Summary

Bubble Sort is great for training and visualizations, but not recommended for large data due to its quadratic time complexity. Its strength is its **simplicity** and the fact that it sorts **in-place**.
