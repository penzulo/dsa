#include <cassert>
#include <vector>

using std::vector;

auto find_min(const vector<int>& nums) -> int {
  size_t left{};
  size_t right{nums.size() - 1};

  while (left < right) {
    const auto mid = (left + right) / 2;

    if (nums.at(mid) > nums.at(right)) {
      left = mid + 1;
      // } else if (nums.at(mid) < nums.at(right)) {
    } else {
      right = mid;
    }
  }
  return nums.at(left);
}

int main() {
  {
    const auto data = {3, 4, 5, 1, 2};
    const auto result = find_min(data);
    assert(result == 1);
  }
  {
    const auto data = {11, 13, 15, 17};
    const auto result = find_min(data);
    assert(result == 11);
  }
  {
    const auto data = {4, 5, 6, 7, 0, 1, 2};
    const auto result = find_min(data);
    assert(result == 0);
  }
  return 0;
}
