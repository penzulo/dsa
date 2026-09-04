# Median of Two Sorted Arrays

## Core Idea
* **Merge Two Sorted Arrays:** Use two iterators to merge both arrays into a single sorted array, similar to the merge step of merge sort.
* **Find Median:** Once merged, the median is the middle element (odd length) or the average of the two middle elements (even length).
* **Reserve Space:** Pre-allocate the result vector with `nums1.size() + nums2.size()` to avoid reallocations during merge.

## Resource Stats

| Resource | Complexity | Justification |
| -------- | ---------- | ------------- |
| Time     | `O(m + n)` | Single pass through both arrays to merge them |
| Space    | `O(m + n)` | The merged result array stores all elements |

## More Approaches
The optimal approach uses binary search on the smaller array to partition both arrays such that the left half contains exactly half the elements. This achieves `O(log(min(m, n)))` time with `O(1)` space, but is significantly more complex to implement.
