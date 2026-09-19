#include <cassert>
#include <ranges>
#include <unordered_map>
#include <vector>

using std::vector, std::unordered_map, std::views::enumerate;

vector<int> two_sum(const vector<int>& nums, const int target) {
  unordered_map<int, int> matches;

  for (const auto& [i, num] : enumerate(nums)) {
    const int complement = target - num;
    const auto& it = matches.find(complement);

    if (it != matches.end()) {
      return {it->second, static_cast<int>(i)};
    }

    matches[nums[static_cast<size_t>(i)]] = static_cast<int>(i);
  }

  return vector<int>{};
}

int main() {
  {
    const vector<int> nums{2, 7, 11, 15};
    const auto result = two_sum(nums, 9);
    assert(result == vector<int>{0, 1});
  }
  {
    const vector<int> nums{3, 2, 4};
    const auto result = two_sum(nums, 6);
    assert(result == vector<int>{1, 2});
  }
  {
    const vector<int> nums{3, 3};
    const auto result = two_sum(nums, 6);
    assert(result == vector<int>{0, 1});
  }

  return 0;
}
