# Longest Palindromic Substring

## Core Idea
* **Expand Around Center:** For each character (and each gap between characters), expand outward while the characters on both sides match.
* **Odd and Even Lengths:** Check both odd-length palindromes (centered on a character) and even-length palindromes (centered between two characters).
* **Track Best Result:** Keep track of the best start index and length found so far. Return the substring using `substr`.

## Resource Stats

| Resource | Complexity | Justification |
| -------- | ---------- | ------------- |
| Time     | `O(n^2)`   | For each of the n centers, expansion can take up to O(n) |
| Space    | `O(1)`     | Only a few variables to track the best palindrome |

## More Approaches
Manacher's algorithm achieves `O(n)` time by reusing previously computed palindrome information, but requires `O(n)` extra space. A dynamic programming approach also exists with `O(n^2)` time and space, but is less elegant.
