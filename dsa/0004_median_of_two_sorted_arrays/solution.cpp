#include <cassert>
#include <vector>

using std::vector;

float find_median(const vector<int>& sample) {
  const auto length = sample.size();
  const auto mid = length / 2;

  if (length % 2 == 1) {
    return static_cast<float>(sample[mid]);
  }

  return (static_cast<float>(sample[mid - 1]) +
          static_cast<float>(sample[mid])) /
         2.0F;
}

float find_median_sorted_arrays(const vector<int>& nums1,
                                const vector<int>& nums2) {
  auto iterator1 = nums1.begin();
  auto iterator2 = nums2.begin();

  vector<int> result;
  result.reserve(nums1.size() + nums2.size());

  while (iterator1 != nums1.end() && iterator2 != nums2.end()) {
    if (*iterator1 < *iterator2) {
      result.emplace_back(*iterator1);
      iterator1++;
    } else {
      result.emplace_back(*iterator2);
      iterator2++;
    }
  }

  result.insert(result.end(), iterator1, nums1.end());
  result.insert(result.end(), iterator2, nums2.end());

  return find_median(result);
}

int main() {
  {
    const auto result = find_median_sorted_arrays({1, 3}, {2});
    const auto expected = 2.0F;
    assert(result == expected);
  }
  {
    const auto result = find_median_sorted_arrays({1, 2}, {3, 4});
    const auto expected = 2.5F;
    assert(result == expected);
  }

  return 0;
}
