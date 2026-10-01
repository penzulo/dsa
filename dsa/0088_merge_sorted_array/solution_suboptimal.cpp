#include <cassert>
#include <cstddef>
#include <vector>

using std::vector, std::size_t;

auto merge(vector<int>& nums1, const int m, const vector<int>& nums2, const int n) {
  // Suboptimal variant: merge into a fresh buffer (O(m + n) extra space),
  // then copy the sorted result back into nums1.
  vector<int> merged;
  merged.reserve(static_cast<size_t>(m + n));

  size_t i{};
  size_t j{};
  const size_t m_size = static_cast<size_t>(m);
  const size_t n_size = static_cast<size_t>(n);

  while (i < m_size && j < n_size) {
    if (nums1[i] < nums2[j]) {
      merged.push_back(nums1[i]);
      ++i;
    } else {
      merged.push_back(nums2[j]);
      ++j;
    }
  }

  while (i < m_size) {
    merged.push_back(nums1[i]);
    ++i;
  }

  while (j < n_size) {
    merged.push_back(nums2[j]);
    ++j;
  }

  nums1 = merged;
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