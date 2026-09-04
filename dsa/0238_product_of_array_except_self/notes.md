# Product of Array Except Self

## Core Idea
* **Prefix and Postfix Products:** For each element, the result is the product of all elements to its left (prefix) multiplied by all elements to its right (postfix).
* **Two-Pass Construction:** First pass fills the result with prefix products. Second pass multiplies in the postfix products.
* **No Division:** This avoids the edge case of zero elements and the restriction of not using division.

## Resource Stats

| Resource | Complexity | Justification |
| -------- | ---------- | ------------- |
| Time     | `O(n)`     | Two linear passes through the array |
| Space    | `O(1)`     | Only uses the output array plus two variables (prefix, postfix) |

## More Approaches
A naive approach computes the total product and divides by each element, but this fails with zeros and violates the "no division" constraint. The prefix/postfix approach elegantly sidesteps both issues.
