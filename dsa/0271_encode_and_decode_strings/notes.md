# Encode and Decode Strings

## Core Idea
* **Length-Prefix Encoding:** Encode each string as `len#string`, where `len` is the string's length and `#` is a delimiter.
* **Unambiguous Decoding:** During decode, find the `#`, read the length, then extract exactly that many characters as the next string.
* **Handles Special Characters:** Because the length is explicit, strings containing `#` or other special characters decode correctly.

## Resource Stats

| Resource | Complexity | Justification |
| -------- | ---------- | ------------- |
| Time     | `O(n)`     | Single pass for both encode and decode (n = total characters) |
| Space    | `O(n)`     | The encoded/decoded output stores all characters |

## More Approaches
Alternative delimiters (like non-ASCII characters) can work but are fragile. The length-prefix approach is the most robust and widely used for this problem.
