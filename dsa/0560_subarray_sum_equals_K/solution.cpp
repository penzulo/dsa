// Problem: https://leetcode.com/problems/subarray-sum-equals-k/
#include <cassert>
#include <unordered_map>
#include <vector>

using std::vector, std::unordered_map;

auto subarray_sum(const vector<int>& nums, const int k) -> int {
  /*
   * Thought Process:
   * We need to return the total *number* of subarrays possible
   * which add up to K.
   * K is an arbitraty number.
   * does the given array guarentee at least 1 element? Yes.
   * is the array sorted? Probably not.
   * Can we benefit from sorting the array? The elements would be local
   * to each other. But we need a contigous subarray anyways so the input
   * might just be sorted.
   *
   * The obvious brute force solution would be to capture all the combinations of
   * contigous elements, increment a counter and return a counter.
   * Empty arrays are not valid subarrays so we can't add them.
   *
   * We can have two pointers - left and right start at index 0 and go up to index n - 1.
   * We increment right in every step and only increment left if the current sum is greater than K.
   *
   * We also cannot add the same number twice. so if nums[left] and nums[right] are pointing to the
   * same number, we cannot move forward with the process. But what if the array contains exactly
   * one element? In that case, either the element IS K (adds up to K) or the count is 0.
   */

  int count{};

  // K: sum of elements up to i, V: frequency of the sum
  unordered_map<int, int> prefix_count{
      {0, 1},
  };
  // Base case. There will always exist a subarray which adds up to 0;

  int current_sum{};

  for (const auto num : nums) {
    current_sum += num;
    const auto diff = current_sum - k;

    count += prefix_count.contains(diff) ? prefix_count[diff] : 0;
    prefix_count[current_sum]++;
  }

  return count;
}

int main() {
  {
    // LeetCode example 1 -> [1, 1] at indices 0-1 and 1-2.
    const vector<int> nums{1, 1, 1};
    assert(subarray_sum(nums, 2) == 2);
  }
  {
    // LeetCode example 2 -> [3] and [1, 2].
    const vector<int> nums{1, 2, 3};
    assert(subarray_sum(nums, 3) == 2);
  }
  {
    // Negatives: [1, -1], [1, -1, 0] and [0] all sum to 0.
    const vector<int> nums{1, -1, 0};
    assert(subarray_sum(nums, 0) == 3);
  }
  {
    // A single matching element.
    const vector<int> nums{3};
    assert(subarray_sum(nums, 3) == 1);
  }
  {
    // A single non-matching element.
    const vector<int> nums{3};
    assert(subarray_sum(nums, 1) == 0);
  }
  return 0;
}
