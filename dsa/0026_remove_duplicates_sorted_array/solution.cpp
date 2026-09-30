#include <cassert>
#include <vector>

using std::vector, std::size_t;

auto remove_duplicates(vector<int>& nums) -> int {
  if (nums.empty()) {
    return 0;
  }

  size_t write{1};

  for (size_t read{1}; read < nums.size(); ++read) {
    if (nums[read] != nums[write - 1]) {
      nums[write] = nums[read];
      ++write;
    }
  }

  return static_cast<int>(write);
}

int main() {
  {
    // Example 1 from the problem statement.
    vector<int> nums{1, 1, 2};
    const auto result = remove_duplicates(nums);
    const vector<int> expected{1, 2};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Example 2 from the problem statement.
    vector<int> nums{0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    const auto result = remove_duplicates(nums);
    const vector<int> expected{0, 1, 2, 3, 4};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Empty input.
    vector<int> nums{};
    const auto result = remove_duplicates(nums);
    assert(result == 0);
  }
  {
    // A single element.
    vector<int> nums{1};
    const auto result = remove_duplicates(nums);
    const vector<int> expected{1};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // No duplicates: input is unchanged.
    vector<int> nums{1, 2, 3, 4};
    const auto result = remove_duplicates(nums);
    const vector<int> expected{1, 2, 3, 4};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Every element is the same value.
    vector<int> nums{7, 7, 7};
    const auto result = remove_duplicates(nums);
    const vector<int> expected{7};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Duplicates grouped at the end.
    vector<int> nums{1, 2, 2, 2};
    const auto result = remove_duplicates(nums);
    const vector<int> expected{1, 2};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Duplicates grouped at the start.
    vector<int> nums{1, 1, 1, 2};
    const auto result = remove_duplicates(nums);
    const vector<int> expected{1, 2};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Duplicates in the middle.
    vector<int> nums{1, 2, 2, 3, 4};
    const auto result = remove_duplicates(nums);
    const vector<int> expected{1, 2, 3, 4};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Duplicates alternating with distinct runs.
    vector<int> nums{1, 1, 2, 2, 3, 3};
    const auto result = remove_duplicates(nums);
    const vector<int> expected{1, 2, 3};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }
  {
    // Negative values are deduplicated too.
    vector<int> nums{-2, -2, -1, 0, 1, 1};
    const auto result = remove_duplicates(nums);
    const vector<int> expected{-2, -1, 0, 1};
    assert(result == static_cast<int>(expected.size()));
    assert(vector<int>(nums.begin(), nums.begin() + result) == expected);
  }

  return 0;
}