#include <cassert>
#include <vector>

using std::vector, std::size_t;

auto remove_element(vector<int>& nums, const int val) -> int {
  size_t write{};

  for (size_t read{}; read < nums.size(); ++read) {
    if (nums[read] != val) {
      nums[write] = nums[read];
      ++write;
    }
  }

  return static_cast<int>(write);
}

int main() {
  {
    // Example 1 from the problem statement.
    vector<int> nums{3, 2, 2, 3};
    const auto result = remove_element(nums, 3);
    const vector<int> expected{2, 2};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Example 2 from the problem statement.
    vector<int> nums{0, 1, 2, 2, 3, 0, 4, 2};
    const auto result = remove_element(nums, 2);
    const vector<int> expected{0, 1, 3, 0, 4};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Empty input.
    vector<int> nums{};
    const auto result = remove_element(nums, 5);
    assert(result == 0);
  }
  {
    // val never occurs: input is unchanged.
    vector<int> nums{1, 2, 3, 4};
    const auto result = remove_element(nums, 9);
    const vector<int> expected{1, 2, 3, 4};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Every element equals val: everything is removed.
    vector<int> nums{7, 7, 7};
    const auto result = remove_element(nums, 7);
    assert(result == 0);
  }
  {
    // Single element that matches.
    vector<int> nums{1};
    const auto result = remove_element(nums, 1);
    assert(result == 0);
  }
  {
    // Single element that does not match.
    vector<int> nums{1};
    const auto result = remove_element(nums, 2);
    const vector<int> expected{1};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // All matches at the start of the array.
    vector<int> nums{1, 1, 2, 3};
    const auto result = remove_element(nums, 1);
    const vector<int> expected{2, 3};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // All matches at the end of the array.
    vector<int> nums{1, 2, 3, 3};
    const auto result = remove_element(nums, 3);
    const vector<int> expected{1, 2};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // One match in the middle; relative order is preserved.
    vector<int> nums{1, 2, 3, 4, 5};
    const auto result = remove_element(nums, 3);
    const vector<int> expected{1, 2, 4, 5};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Mixed matches sprinkled through the array.
    vector<int> nums{4, 1, 2, 1, 3, 1};
    const auto result = remove_element(nums, 1);
    const vector<int> expected{4, 2, 3};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }

  return 0;
}