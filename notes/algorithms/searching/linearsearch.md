# Linear Search: The Simplest Search Algorithm

Linear Search is the most straightforward method for finding an element in a collection. It works by sequentially checking each element of the list until the desired value is found or the end is reached.

---

## 🔑 How Linear Search Works

1. **Start at the beginning:**
   Begin with the first element of the array or list.

2. **Compare each element:**
   Check if the current element matches the target value.

3. **Continue or stop:**
   - If a match is found, return the index or indicate success.
   - If not, move to the next element.

4. **Repeat:**
   Continue this process until the item is found or the end of the list is reached.

---

## Step-by-Step Example

Suppose you have the array: `[7, 2, 9, 4, 1]`
And you want to search for the value `4`:

- Compare `7` (no match)
- Compare `2` (no match)
- Compare `9` (no match)
- Compare `4` (**match!**) → Return index `3` (if 0-based indexing)

If the value were not present, the search would end after the last element.

---

## Time and Space Complexity

- **Worst-Case Time Complexity:** `O(n)`
  The algorithm must check every element (especially if the value is not present).

- **Best-Case Time Complexity:** `O(1)`
  The target matches the first element.

- **Average-Case Time Complexity:** `O(n)`
  On average, it checks about half the elements.

- **Space Complexity:** `O(1)` (in-place)
  Linear Search doesn't require extra storage besides a few variables.

---

## Summary

- Linear Search is easy to understand and implement.
- Best for short or unsorted lists.
- Not efficient for large datasets, but useful when simplicity is more important than speed.
