# Group Anagrams

## Core Idea
* **Character Frequency as Key:** For each string, build a frequency count of its characters (26 lowercase letters) and use this as a hash map key.
* **Hash Map Grouping:** Strings with identical frequency maps are anagrams and get grouped together under the same key.
* **Result Collection:** Collect all groups from the hash map into the output vector. Use a `normalize` helper to sort groups for consistent test comparison.

## Resource Stats

| Resource | Complexity | Justification |
| -------- | ---------- | ------------- |
| Time     | `O(n * k)` | n strings, each of length k, processed to build frequency keys |
| Space    | `O(n * k)` | Hash map stores all strings grouped by their keys |

## More Approaches
A simpler approach sorts each string alphabetically to produce the key (e.g., "eat" → "aet"), but sorting each string costs `O(k log k)` per string, making total time `O(n * k log k)`. The frequency count approach avoids this by counting in `O(k)`.
