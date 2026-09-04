#include <cassert>
#include <unordered_map>
#include <vector>

// @note We don't really need a counter. We just need to check
// if the number has been seen before.

bool contains_duplicates(const std::vector<int>& sample) {
  std::unordered_map<int, int> frequency_counter;  // K: number, V: frequency
  for (const auto& num : sample) {
    frequency_counter[num]++;
    if (frequency_counter[num] > 1) {
      return true;
    }
  }
  return false;
}

int main() {
  {
    const auto result = contains_duplicates({1, 2, 3, 1});
    assert(result);
  }
  {
    const auto result = contains_duplicates({1, 2, 3, 4});
    assert(!result);
  }
  {
    const auto result = contains_duplicates({1, 1, 1, 3, 3, 4, 3, 2, 4, 2});
    assert(result);
  }

  return 0;
}
