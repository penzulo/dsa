#include <cassert>
#include <unordered_set>
#include <vector>

using std::vector, std::unordered_set;

int longest_consecutive(const vector<int>& nums) {
  if (nums.empty()) {
    return 0;
  }

  int result{};
  unordered_set<int> seen;

  for (const auto num : nums) {
    if (seen.contains(num)) {
      continue;
    }

    const int next = num + 1;
    const auto& it = std::ranges::find(nums, next);

    if (it != nums.end()) {
      ++result;
    }
    seen.insert(num);
  }

  return result + 1;
}

int main() {
  {
    assert(longest_consecutive({100, 4, 200, 1, 3, 2}) == 4);
    assert(longest_consecutive({0, 3, 7, 2, 5, 8, 4, 6, 0, 1}) == 9);
    assert(longest_consecutive({1, 0, 1, 2}) == 3);
  }
  return 0;
}
