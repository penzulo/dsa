#include <cassert>
#include <vector>

using std::vector, std::size_t;

auto search_insert(const vector<int>& nums, const int target) -> int {
  if (nums.empty()) {
    return 0;
  }

  int left{};
  auto right{static_cast<int>(nums.size() - 1)};

  while (left <= right) {
    const auto middle = static_cast<size_t>((left + right) / 2);
    if (nums[middle] == target) {
      return static_cast<int>(middle);
    }

    if (nums[middle] > target) {
      right = static_cast<int>(middle) - 1;
    } else {
      left = static_cast<int>(middle) + 1;
    }
  }

  return left;
}

int main() {
  {
    // Example 1 from the problem statement.
    const auto result = search_insert({1, 3, 5, 6}, 5);
    const auto expected{2};
    assert(result == expected);
  }
  {
    // Example 2 from the problem statement.
    const auto result = search_insert({1, 3, 5, 6}, 2);
    const auto expected{1};
    assert(result == expected);
  }
  {
    // Example 3 from the problem statement.
    const auto result = search_insert({1, 3, 5, 6}, 7);
    const auto expected{4};
    assert(result == expected);
  }
  {
    // Example 4 from the problem statement.
    const auto result = search_insert({1, 3, 5, 6}, 0);
    const auto expected{0};
    assert(result == expected);
  }
  {
    // Single element: insert before it.
    const auto result = search_insert({1}, 0);
    const auto expected{0};
    assert(result == expected);
  }
  {
    // Single element: insert after it.
    const auto result = search_insert({1}, 2);
    const auto expected{1};
    assert(result == expected);
  }
  {
    // Single element: exact match.
    const auto result = search_insert({1}, 1);
    const auto expected{0};
    assert(result == expected);
  }
  {
    // Two elements, target sits between them.
    const auto result = search_insert({1, 3}, 2);
    const auto expected{1};
    assert(result == expected);
  }
  {
    // Two elements: exact match at the end.
    const auto result = search_insert({1, 3}, 3);
    const auto expected{1};
    assert(result == expected);
  }
  {
    // Two elements: smaller than everything.
    const auto result = search_insert({1, 3}, 0);
    const auto expected{0};
    assert(result == expected);
  }
  {
    // Duplicates: matches the first occurrence.
    const auto result = search_insert({1, 2, 2, 3}, 2);
    const auto expected{1};
    assert(result == expected);
  }
  {
    // Larger array, target falls between two elements.
    const auto result = search_insert({1, 3, 5, 6, 8, 10}, 9);
    const auto expected{5};
    assert(result == expected);
  }
  {
    // Empty input inserts at position zero.
    const auto result = search_insert({}, 5);
    const auto expected{0};
    assert(result == expected);
  }

  return 0;
}