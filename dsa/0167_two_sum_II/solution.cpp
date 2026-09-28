#include <cassert>
#include <vector>

using std::vector, std::size_t;

vector<int> two_sum(const vector<int>& numbers, const int target) {
  if (numbers.size() < 2) {
    return {};
  }

  size_t left{};
  size_t right{numbers.size() - 1};

  while (left < right) {
    const int sum = numbers[left] + numbers[right];

    if (sum == target) {
      return {static_cast<int>(left + 1), static_cast<int>(right + 1)};
    }

    if (sum < target) {
      ++left;
    } else {
      --right;
    }
  }

  return {};
}

int main() {
  {
    const vector<int> nums{2, 7, 11, 15};
    const auto result = two_sum(nums, 9);
    assert(result == vector<int>{1, 2});
  }
  {
    const vector<int> nums{2, 3, 4};
    const auto result = two_sum(nums, 6);
    assert(result == vector<int>{1, 3});
  }
  {
    const vector<int> nums{-1, 0};
    const auto result = two_sum(nums, -1);
    assert(result == vector<int>{1, 2});
  }

  return 0;
}
