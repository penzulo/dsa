#include <cassert>
#include <ranges>
#include <vector>

using std::vector, std::ranges::views::enumerate, std::size_t;

auto get_concatenation(const vector<int>& nums) -> vector<int> {
  vector<int> result(nums.size() * 2);

  for (const auto [i, num] : enumerate(nums)) {
    result[static_cast<size_t>(i)] = num;
    result[static_cast<size_t>(i) + nums.size()] = num;
  }

  return result;
}

int main() {
  {
    const auto result = get_concatenation({1, 2, 1});
    const vector<int> expected{1, 2, 1, 1, 2, 1};
    assert(result == expected);
  }
  {
    const auto result = get_concatenation({1, 3, 2, 1});
    const vector<int> expected{1, 3, 2, 1, 1, 3, 2, 1};
    assert(result == expected);
  }

  return 0;
}
