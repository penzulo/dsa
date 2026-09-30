#include <cassert>
#include <cstddef>
#include <vector>

using std::vector, std::size_t;

auto merge(vector<int>& nums1, const int m, const vector<int>& nums2, const int n) {
  // Walk both arrays backwards, filling nums1's tail. Counters are
  // one-past-end so they stay unsigned (no `- 1` underflow) and the loop
  // ends as soon as nums2 is exhausted: nums1's remaining elements are
  // already in their final position.
  size_t i{static_cast<size_t>(m)};
  size_t j{static_cast<size_t>(n)};
  size_t k{static_cast<size_t>(m + n)};

  while (j > 0) {
    if (i > 0 && nums1[i - 1] > nums2[j - 1]) {
      nums1[k - 1] = nums1[i - 1];
      --i;
    } else {
      nums1[k - 1] = nums2[j - 1];
      --j;
    }
    --k;
  }
}

int main() {
  {
    // Example 1 from the problem statement.
    vector<int> nums1{1, 2, 3, 0, 0, 0};
    const vector<int> nums2{2, 5, 6};
    merge(nums1, 3, nums2, 3);
    const vector<int> expected{1, 2, 2, 3, 5, 6};
    assert(nums1 == expected);
  }
  {
    // Example 2: nums2 is empty, nothing to merge.
    vector<int> nums1{1};
    const vector<int> nums2{};
    merge(nums1, 1, nums2, 0);
    const vector<int> expected{1};
    assert(nums1 == expected);
  }
  {
    // Example 3: nums1 is "empty"; only the trailing slot exists.
    vector<int> nums1{0};
    const vector<int> nums2{1};
    merge(nums1, 0, nums2, 1);
    const vector<int> expected{1};
    assert(nums1 == expected);
  }
  {
    // All of nums2 is smaller than all of nums1.
    vector<int> nums1{4, 5, 6, 0, 0, 0};
    const vector<int> nums2{1, 2, 3};
    merge(nums1, 3, nums2, 3);
    const vector<int> expected{1, 2, 3, 4, 5, 6};
    assert(nums1 == expected);
  }
  {
    // All of nums2 is larger than all of nums1.
    vector<int> nums1{1, 2, 3, 0, 0, 0};
    const vector<int> nums2{4, 5, 6};
    merge(nums1, 3, nums2, 3);
    const vector<int> expected{1, 2, 3, 4, 5, 6};
    assert(nums1 == expected);
  }
  {
    // Interleaved values, including a duplicate.
    vector<int> nums1{1, 2, 4, 0, 0, 0};
    const vector<int> nums2{1, 3, 5};
    merge(nums1, 3, nums2, 3);
    const vector<int> expected{1, 1, 2, 3, 4, 5};
    assert(nums1 == expected);
  }
  {
    // Heavy duplicates across both inputs.
    vector<int> nums1{1, 1, 1, 0, 0, 0};
    const vector<int> nums2{1, 1, 1};
    merge(nums1, 3, nums2, 3);
    const vector<int> expected{1, 1, 1, 1, 1, 1};
    assert(nums1 == expected);
  }
  {
    // Single element each; nums2 element is smaller.
    vector<int> nums1{2, 0};
    const vector<int> nums2{1};
    merge(nums1, 1, nums2, 1);
    const vector<int> expected{1, 2};
    assert(nums1 == expected);
  }
  {
    // Single element each; nums1 element is smaller.
    vector<int> nums1{1, 0};
    const vector<int> nums2{2};
    merge(nums1, 1, nums2, 1);
    const vector<int> expected{1, 2};
    assert(nums1 == expected);
  }
  {
    // Both inputs are empty.
    vector<int> nums1{};
    const vector<int> nums2{};
    merge(nums1, 0, nums2, 0);
    const vector<int> expected{};
    assert(nums1 == expected);
  }

  return 0;
}