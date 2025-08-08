# Binary Search: An Efficient Search Algorithm for Sorted Data

Binary Search is a fast algorithm for finding a target value within a **sorted** collection (such as an array or list). It repeatedly divides the search interval in half, discarding the half where the target cannot lie.

---

## 🔑 How Binary Search Works

1. **Start with the sorted array:**
   Identify the start (`low`) and end (`high`) indices of the array.

2. **Find the middle element:**
   Calculate the middle index:
   `mid = (low + high) // 2`

3. **Compare the middle element:**
   - If it equals the target value, **success!**
   - If the target is less than the middle element, search the left half:
     Set `high = mid - 1`
   - If the target is greater than the middle element, search the right half:
     Set `low = mid + 1`

4. **Repeat:**
   Continue the process with the remaining half, updating `low` and `high` each step, until the target is found or the subarray is empty.

> **Note:** Binary Search only works on sorted data!

---

## Step-by-Step Example

Suppose you have the array: `[1, 3, 5, 7, 9, 11]`
And you want to search for the value `7`:

1. `low = 0`, `high = 5`
2. `mid = (0 + 5) // 2 = 2` → value is `5`
   - `7` is greater than `5`, so search right half: `low = 3`
3. `mid = (3 + 5) // 2 = 4` → value is `9`
   - `7` is less than `9`, so search left half: `high = 3`
4. `mid = (3 + 3) // 2 = 3` → value is `7`
   - **Found!** Return index `3`.

---

## Time and Space Complexity

- **Worst-Case Time Complexity:** `O(log n)`
  Each step halves the search range, so the number of steps grows logarithmically with the array size.

- **Best-Case Time Complexity:** `O(1)`
  The target is found at the middle in the first step.

- **Average-Case Time Complexity:** `O(log n)`

- **Space Complexity:**
  - **Iterative:** `O(1)` (in-place; no extra storage needed)
  - **Recursive:** `O(log n)` (due to call stack space)

---

## Summary

- Binary Search is much faster than Linear Search for large **sorted** data.
- It is not suitable for unsorted arrays.
- Binary Search is widely used in computer science due to its efficiency and simplicity.
