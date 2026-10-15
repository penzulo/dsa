// Problem: https://leetcode.com/problems/maximum-subarray/
#include <algorithm>
#include <cassert>
#include <vector>

using std::vector;

auto max_subarray(const vector<int>& nums) -> int {
  int max_sum{nums[0]};
  int current_sum{nums[0]};

  for (size_t i{1}; i < nums.size(); i++) {
    current_sum = std::max(nums[i], current_sum + nums[i]);
    max_sum = std::max(max_sum, current_sum);
  }

  return max_sum;
}

int main() {
  {
    // LeetCode example 1 -> the subarray [4, -1, 2, 1] sums to 6.
    const vector<int> nums{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    assert(max_subarray(nums) == 6);
  }
  {
    // A single positive element.
    const vector<int> nums{1};
    assert(max_subarray(nums) == 1);
  }
  {
    // LeetCode example 3 -> the whole array sums to 23.
    const vector<int> nums{5, 4, -1, 7, 8};
    assert(max_subarray(nums) == 23);
  }
  {
    // All negative: the best subarray is the single largest element.
    const vector<int> nums{-3, -1, -2};
    assert(max_subarray(nums) == -1);
  }
  {
    // A single negative element.
    const vector<int> nums{-1};
    assert(max_subarray(nums) == -1);
  }
  {
    // A zero can extend a subarray without hurting it.
    const vector<int> nums{-2, 0, -1};
    assert(max_subarray(nums) == 0);
  }
  return 0;
}
