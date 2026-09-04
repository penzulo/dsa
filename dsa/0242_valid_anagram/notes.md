# Valid Anagram

## Core Idea
* **Single Frequency Array:** Use one 26-element array. Increment for characters in s1, decrement for s2.
* **One-Pass Check:** Process both strings simultaneously in a single loop. If all counts are zero at the end, they are anagrams.
* **Early Size Check:** Return false immediately if the strings differ in length.

## Resource Stats

| Resource | Complexity | Justification |
| -------- | ---------- | ------------- |
| Time     | `O(n)`     | Single pass through both strings |
| Space    | `O(1)`     | Fixed 26-element array regardless of input size |

## More Approaches
Sorting both strings and comparing them is `O(n log n)` time. Using two separate hash maps works but uses more space than a fixed-size array.
