#include <cassert>
#include <print>
#include <ranges>
#include <unordered_map>
#include <vector>

using std::vector, std::unordered_map, std::views::enumerate;

vector<int> two_sum(const vector<int>& nums, const int target) {
  unordered_map<int, int> matches;

  for (size_t i = 0; i < nums.size(); i++) {
    const auto& num = nums[i];
    const int complement = target - num;

    if (const auto& it = matches.find(complement); it != matches.end()) {
      return vector<int>{it->second, static_cast<int>(i)};
    }

    matches[nums[i]] = static_cast<int>(i);
  }

  return vector<int>{};
}

int main() {
  {
    vector<int> nums{2, 7, 11, 15};
    auto result = two_sum(nums, 9);
    assert(result == vector<int>{0, 1});
  }
  {
    vector<int> nums{3, 2, 4};
    auto result = two_sum(nums, 6);
    assert(result == vector<int>{1, 2});
  }
  {
    vector<int> nums{3, 3};
    auto result = two_sum(nums, 6);
    assert(result == vector<int>{0, 1});
  }

  std::println("all tests passed");
  return 0;
}
