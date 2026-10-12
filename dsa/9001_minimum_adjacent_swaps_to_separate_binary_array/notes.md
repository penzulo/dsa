# Minimum Adjacent Swaps to Separate Binary Array

Amazon OA (not a LeetCode problem; tracked as synthetic id `9001`).

## Problem

Given a binary array `nums` of `0`s and `1`s, in one move you can swap two
adjacent elements. Return the minimum number of moves to make all `0`s appear
together and all `1`s appear together. The order of the two groups does not
matter (`0`...`0 1`...`1` or `1`...`1 0`...`0`).

Constraints: `1 <= nums.length <= 10^5`, `nums[i] in {0, 1}`.

## Examples

| Input                  | Output | Notes                                              |
| ---------------------- | ------ | -------------------------------------------------- |
| `[0, 1, 0, 1]`         | `1`    | swap `nums[1]` and `nums[2]`                       |
| `[1, 1, 1, 1, 0, 0, 0]`| `0`    | already separated                                  |
| `[1, 0, 1, 0, 0]`      | `1`    | 1s-first needs 1, 0s-first needs 5                 |

> The OA statement's Example 3 is internally inconsistent. For
> `[1, 0, 1, 0, 0]` the true minimum is **1**: swapping indices 1 and 2
> yields `[1, 1, 0, 0, 0]` directly. The writeup claims "Scenario B: 2
> swaps", but its own goal array is reachable in one; it also claims
> "Scenario A: 4 swaps" while its trace lists five. Both scenario costs in
> the statement are off, and the min of the corrected costs is `1`.

## Approach

There are exactly two valid final layouts, so evaluate both and take the min —
**without touching the array**.

- Layout "1s first": each `1` moves left past every `0` seen before it.
  Accumulate `seen_zeros` as we scan; when we hit a `1`, add `seen_zeros`.
- Layout "0s first": symmetric, accumulate `seen_ones` when hitting a `0`.

Every "1 before 0" (or "0 before 1") adjacent pair that must be crossed costs
exactly one swap, and adjacent swaps cannot do better, so the sum is exact.

## Complexity

| Resource | Complexity |
| -------- | ---------- |
| Time     |   `O(n)`   |
| Space    |   `O(1)`   |

## What I tried and missed

- Two pointers / sliding window: not the right shape here; the cost is a sum
  of crossings, not a range query.
- Bubble-sort-like mutation: correct in spirit (adjacent swaps) but you do not
  need to actually perform them; the swap count is a pure function of the
  counts seen so far.
- "Which half has more of X": incomplete; the two-orderings enumeration is the
  missing half of that thought.
- The insight: the minimum is over *both* positions of the boundary, which is
  exactly the min of the two running counters.

## Reference (Python)

```python
def min_swaps(nums: list[int]) -> int:
    swaps_0_first, swaps_1_first = 0, 0
    seen = {0: 0, 1: 0}
    for n in nums:
        if n == 1:
            seen[1] += 1
            swaps_1_first += seen[0]
        else:
            seen[0] += 1
            swaps_0_first += seen[1]
    return min(swaps_0_first, swaps_1_first)
```