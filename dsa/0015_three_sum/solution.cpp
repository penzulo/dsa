#include <algorithm>
#include <cassert>
#include <vector>

using std::vector, std::size_t;
using result_t = vector<vector<int>>;

auto three_sum(vector<int>& nums) -> result_t {
  result_t result;
  // unordered_set<int> seen;
  // 1. Sort the Array
  std::ranges::sort(nums);

  // 2. Loop through each element in the array
  // for (size_t i{}; i < nums.size(); ++i) {
  // What if nums.size() == 0?
  for (size_t i{}; i + 2 < nums.size(); ++i) {
    // if (!seen.insert(nums[i]).second) {
    //   continue;
    // }
    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }

    size_t left{i + 1};
    size_t right{nums.size() - 1};  // This would result in a big number if `nums` is empty

    while (left < right) {
      const int sum = nums[i] + nums[left] + nums[right];

      if (sum < 0) {
        ++left;
      } else if (sum > 0) {
        --right;
      } else {
        result.emplace_back(vector<int>{nums[i], nums[left], nums[right]});
        ++left;
        --right;

        while (left < right && nums[left] == nums[left - 1]) {
          ++left;
        }

        while (left < right && nums[right] == nums[right + 1]) {
          --right;
        }
      }
    }
  }

  return result;
}

int main() {
  {
    // sorted = -4, -1, -1, 0, 1, 2
    auto data = vector<int>{-1, 0, 1, 2, -1, -4};
    const auto result = three_sum(data);
    const result_t expected = {{-1, -1, 2}, {-1, 0, 1}};
    assert(result == expected);
  }
  {
    // sorted = -4, -1, -1, 0, 1, 2
    auto data = vector<int>{0, 1, 1};
    const auto result = three_sum(data);
    const result_t expected = {};
    assert(result == expected);
  }
  {
    // sorted = -4, -1, -1, 0, 1, 2
    auto data = vector<int>{0, 0, 0};
    const auto result = three_sum(data);
    const result_t expected = {{0, 0, 0}};
    assert(result == expected);
  }
  {
    // sorted = -4, -1, -1, 0, 1, 2
    auto data = vector<int>{0, 0, 0, 0};
    const auto result = three_sum(data);
    const result_t expected = {{0, 0, 0}};
    assert(result == expected);
  }
  return 0;
}
