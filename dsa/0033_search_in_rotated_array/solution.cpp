#include <cassert>
#include <vector>

using std::vector;

auto search(const vector<int>& nums, int target) -> int {
  size_t left{};
  size_t right{nums.size()};

  while (left <= right) {
    const auto mid = left + ((right - left) / 2);

    if (nums[mid] == target) {
      return static_cast<int>(mid);
    }

    if (nums[left] <= nums[mid]) {
      if (nums[left] <= target && target < nums[mid]) {
        right = mid;
      } else {
        left = mid + 1;
      }
    } else {
      if (nums[mid] <= target && target < nums[right - 1]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
  }

  return -1;
}

int main() {
  {
    const auto data = {4, 5, 6, 7, 0, 1, 2};
    const auto expected = 4;
    assert(search(data, 0) == expected);
  }
  return 0;
}
