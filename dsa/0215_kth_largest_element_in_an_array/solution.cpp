// Problem: https://leetcode.com/problems/kth-largest-element-in-an-array/

#include <cassert>
#include <queue>
#include <vector>

using std::vector;

// Failed to see that a window of exactly k elements in a priority queue (min-heap)
// will have the kth largest element as exactly the smallest spot in the queue and that
// the kth largest element in the array is just the top value of the min-heap.
auto find_kth_largest(const vector<int>& nums, const int k) -> int {
  const auto count = static_cast<size_t>(k);
  std::priority_queue<int, vector<int>, std::greater<>> heap{nums.begin(), nums.begin() + k};

  for (size_t i{count}; i < nums.size(); ++i) {
    if (nums.at(i) > heap.top()) {
      heap.pop();
      heap.push(nums.at(i));
    }
  }

  return heap.top();
}

int main() {
  {
    const vector<int> nums{3, 2, 1, 5, 6, 4};
    assert(find_kth_largest(nums, 2) == 5);
  }
  {
    const vector<int> nums{3, 2, 3, 1, 2, 4, 5, 5, 6};
    assert(find_kth_largest(nums, 4) == 4);
  }
  return 0;
}
