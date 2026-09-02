# Returns indices of two numbers that add up to target.

## Implementation
This approach makes use of a hash map to store seen values for `0(1)` lookups. For each element, check if its complement `(target - num)` has been seen.

## Resource Stats

| Resource | Complexity |
| -------- | ---------- |
| Time     |   `O(n)`   |
| Space    |   `O(n)`   |

## More approaches
The most primitive way to solve this is using the brute force technique where we make use of nested for loops and check of every combination of two numbers like bubble sort. It is a bad approach because we'd have two nested loops and an condition check nested deep inside them.
