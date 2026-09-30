#include <cstddef>
#include <vector>

using std::vector, std::size_t;

auto merge(vector<int>& nums1, const int m, const vector<int>& nums2, const int n) {
  auto i{static_cast<size_t>(m - 1)};
  auto j{static_cast<size_t>(n - 1)};
  auto k{static_cast<size_t>(m + n - 1)};

  while (j > 0) {
    if (i > 0 && nums1[i] > nums2[j]) {
      nums1[k] = nums1[i];
      --i;
    } else {
      nums1[k] = nums2[j];
      --j;
    }
    --k;
  }
}
