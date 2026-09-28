#include <algorithm>
#include <cassert>
#include <vector>

using std::vector, std::max, std::min;

auto max_area(const vector<int>& height) noexcept -> int {
  size_t area{};
  size_t left{};
  size_t right{height.size() - 1};

  while (left < right) {
    const auto amt = (right - left) * static_cast<size_t>(min(height[left], height[right]));
    area = max(amt, area);

    if (height[left] > height[right]) {
      --right;
    } else {
      ++left;
    }
  }

  return static_cast<int>(area);
}

int main() {
  {
    assert(max_area({1, 8, 6, 2, 5, 4, 8, 3, 7}) == 49);
    assert(max_area({1, 1}) == 1);
  }
  return 0;
}
