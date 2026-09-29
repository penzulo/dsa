#include <algorithm>
#include <cassert>
#include <vector>

using std::vector;

auto find_max_consecutive_ones(const vector<int>& nums) -> int {
  int longest{};
  int current{};

  for (const auto num : nums) {
    if (num == 1) {
      ++current;
      longest = std::max(current, longest);
    } else {
      current = 0;
    }
  }

  return longest;
}

int main() {
  {
    // Example from the problem statement.
    const auto result = find_max_consecutive_ones({1, 1, 0, 1, 1, 1});
    const auto expected{3};
    assert(result == expected);
  }
  {
    // All ones.
    const auto result = find_max_consecutive_ones({1, 1, 1, 1});
    const auto expected{4};
    assert(result == expected);
  }
  {
    // No ones at all.
    const auto result = find_max_consecutive_ones({0, 0, 0, 0});
    const auto expected{0};
    assert(result == expected);
  }
  {
    // A lone one with zeros on both sides.
    const auto result = find_max_consecutive_ones({0, 0, 1, 0});
    const auto expected{1};
    assert(result == expected);
  }
  {
    // Never two ones in a row.
    const auto result = find_max_consecutive_ones({0, 1, 0, 1, 0, 1});
    const auto expected{1};
    assert(result == expected);
  }
  {
    // A run hugging the start of the array.
    const auto result = find_max_consecutive_ones({1, 1, 1, 0, 0});
    const auto expected{3};
    assert(result == expected);
  }
  {
    // A run at the very end of the array.
    const auto result = find_max_consecutive_ones({0, 0, 1, 1, 1});
    const auto expected{3};
    assert(result == expected);
  }
  {
    // Several runs; the longest sits in the middle.
    const auto result = find_max_consecutive_ones({1, 0, 1, 1, 0, 1, 1, 1, 0});
    const auto expected{3};
    assert(result == expected);
  }
  {
    // Empty input.
    const auto result = find_max_consecutive_ones({});
    const auto expected{0};
    assert(result == expected);
  }

  return 0;
}
