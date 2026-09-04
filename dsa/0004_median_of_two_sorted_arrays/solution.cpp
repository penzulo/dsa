#include <cassert>
#include <print>
#include <vector>

float find_median(const std::vector<int>& sample) {
  const auto length = sample.size();
  const auto mid = length / 2;

  if (length % 2 == 1) {
    return static_cast<float>(sample[mid]);
  }

  return (static_cast<float>(sample[mid - 1]) +
          static_cast<float>(sample[mid])) /
         2.0F;
}

float find_median_sorted_arrays(const std::vector<int>& nums1,
                                const std::vector<int>& nums2) {
  auto iterator1 = nums1.begin();
  auto iterator2 = nums2.begin();

  std::vector<int> result;
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
    assert(find_median_sorted_arrays({1, 3}, {2}) == 2.0F);
    assert(find_median_sorted_arrays({1, 2}, {3, 4}) == 2.5F);
  }

  std::println("all tests passed");
  return 0;
}
