#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

using std::vector, std::size_t;

auto trap(const vector<int>& height) -> int {
  // Determine how much water can sit above one index?
  // Determine the information needed for that calculation
  // Precompute the information needed
  // Subtract the terrain from precomputed information
  // Sum the values from the difference and return

  vector<int> max_left(height.size());
  vector<int> max_right(height.size());
  vector<int> water_levels(height.size());

  max_left[0] = height[0];

  for (size_t i{1}; i < height.size(); ++i) {
    max_left[i] = std::max(max_left[i - 1], height[i]);
  }

  max_right.back() = height.back();

  for (size_t i{height.size() - 1}; i > 0; --i) {
    max_right[i - 1] = std::max(max_right[i], height[i - 1]);
  }

  for (size_t i{}; i < height.size(); ++i) {
    water_levels[i] = std::min(max_left[i], max_right[i]) - height[i];
  }

  return std::accumulate(water_levels.begin(), water_levels.end(), 0);
}

int main() {
  {
    // Example 1 from the problem statement.
    const auto result = trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1});
    const auto expected{6};
    assert(result == expected);
  }
  {
    // Example 2 from the problem statement.
    const auto result = trap({4, 2, 0, 3, 2, 5});
    const auto expected{9};
    assert(result == expected);
  }
  {
    // A single peak taller than its neighbours traps nothing.
    const auto result = trap({0, 1, 0});
    const auto expected{0};
    assert(result == expected);
  }
  {
    // A simple bowl between two walls.
    const auto result = trap({1, 0, 1});
    const auto expected{1};
    assert(result == expected);
  }
  {
    // Flat terrain stores no water.
    const auto result = trap({0, 0, 0});
    const auto expected{0};
    assert(result == expected);
  }
  {
    // A single bar stores no water.
    const auto result = trap({1});
    const auto expected{0};
    assert(result == expected);
  }
  {
    // Two bars cannot trap water between them.
    const auto result = trap({1, 2});
    const auto expected{0};
    assert(result == expected);
  }
  {
    // Symmetric walls around a pit.
    const auto result = trap({2, 0, 2});
    const auto expected{2};
    assert(result == expected);
  }
  {
    // A wide pit between equal walls.
    const auto result = trap({3, 0, 0, 3});
    const auto expected{6};
    assert(result == expected);
  }
  {
    // Strictly increasing heights hold no water.
    const auto result = trap({1, 2, 3, 4, 5});
    const auto expected{0};
    assert(result == expected);
  }
  {
    // Strictly decreasing heights hold no water.
    const auto result = trap({5, 4, 3, 2, 1});
    const auto expected{0};
    assert(result == expected);
  }
  {
    // Alternating peaks and pits.
    const auto result = trap({5, 1, 5, 1, 5});
    const auto expected{8};
    assert(result == expected);
  }

  return 0;
}