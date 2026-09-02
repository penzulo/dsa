### Core Idea
* **Dynamic Sliding Window:** Uses two pointers (`left` and `right`) to track the current valid substring.
* **$O(1)$ State Tracking:** Uses a 256-size array `last_seen` to store the most recent index of each character, avoiding slow hash map lookups.
* **Instant Window Shrinking (The Jump):** If a duplicate character is found *inside* the current window (`last_seen[c] >= left`), the `left` pointer instantly jumps past the duplicate's previous index. No inner `while` loop needed!
* **Updating the Maximum:** Calculates `right - left + 1` at each step to update `max_length`.

### Resource Stats

| Resource | Complexity | Justification |
| :--- | :--- | :--- |
| **Time** | $O(N)$ | Single-pass traversal. `right` iterates exactly $N$ times, and `left` only jumps forward. ⏱️ |
| **Space** | $O(1)$ | Fixed-size array of 256 integers, regardless of string length. 💾 |

