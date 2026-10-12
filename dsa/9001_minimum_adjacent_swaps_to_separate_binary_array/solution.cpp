// Problem: Minimum Adjacent Swaps to Separate Binary Array
// Source: Amazon OA (not on LeetCode)
// In one move you can swap two adjacent elements of a binary array.
// Return the minimum number of moves that make all 0s appear together
// and all 1s appear together; the order of the two groups does not matter.
//
// Examples:
//   [0, 1, 0, 1]           -> 1
//   [1, 1, 1, 1, 0, 0, 0]  -> 0
//   [1, 0, 1, 0, 0]        -> 1   (0s-first needs 5, 1s-first needs 1;
//    the OA statement claims "2" but its own Scenario B trace is one swap
//    short, and its "Scenario A: 4" is also wrong -- the trace shows five)
#include <algorithm>
#include <cassert>
#include <vector>

using std::vector, std::size_t;

// What I failed to see: no array mutation is needed. For each of the two
// final group orderings we only count, per element, how many opposing
// elements it must cross, and every crossing is exactly one adjacent swap.
// What I got right: considering both orderings and keeping two counters.
auto min_swaps(const vector<int>& nums) -> size_t {
  size_t zero_first = 0;  // cost of all 0s before all 1s
  size_t one_first = 0;   // cost of all 1s before all 0s
  size_t zeros = 0;
  size_t ones = 0;

  for (const int n : nums) {
    if (n == 1) {
      one_first += zeros;  // this 1 moves left past every 0 seen so far
      ++ones;
    } else {
      zero_first += ones;  // this 0 moves left past every 1 seen so far
      ++zeros;
    }
  }

  return std::min(zero_first, one_first);
}

int main() {
  {
    // Example 1: swap nums[1] and nums[2].
    assert(min_swaps({0, 1, 0, 1}) == 1);
  }
  {
    // Example 2: already separated.
    assert(min_swaps({1, 1, 1, 1, 0, 0, 0}) == 0);
  }
  {
    // Example 3: 0s-first needs 5 swaps, 1s-first needs 1 -> 1.
    // (The OA statement claims "2" but its own Scenario B trace is one
    // swap short: swapping indices 1 and 2 gives [1,1,0,0,0] directly.)
    assert(min_swaps({1, 0, 1, 0, 0}) == 1);
  }
  {
    // Single-element and homogeneous arrays are already separated.
    assert(min_swaps({0}) == 0);
    assert(min_swaps({1}) == 0);
    assert(min_swaps({0, 0, 0}) == 0);
    assert(min_swaps({1, 1, 1}) == 0);
  }
  {
    // [1,0,0,1] -> [0,0,1,1] in two adjacent swaps.
    assert(min_swaps({1, 0, 0, 1}) == 2);
  }
  {
    // Mixed case: 1s-first costs 5.
    assert(min_swaps({1, 0, 1, 0, 1, 1, 0}) == 5);
  }

  return 0;
}
