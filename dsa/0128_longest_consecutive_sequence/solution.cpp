#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <vector>

using std::vector, std::unordered_set;

int longest_consecutive(const vector<int>& nums) {
  // We do this to get rid of duplicates and reduce the
  // search space which decreases the amount of time taken
  // for execution.
  unordered_set<int> numbers(nums.begin(), nums.end());
  int longest{};

  for (const int num : numbers) {
    // If a previous number exists, don't start here
    if (numbers.contains(num - 1)) {
      continue;
    }

    int current{num};
    int length{1};

    while (numbers.contains(current + 1)) {
      ++current;
      ++length;
    }

    longest = std::max(longest, length);
  }

  return longest;
}

int main() {
  {
    assert(longest_consecutive({100, 4, 200, 1, 3, 2}) == 4);
    assert(longest_consecutive({0, 3, 7, 2, 5, 8, 4, 6, 0, 1}) == 9);
    assert(longest_consecutive({1, 0, 1, 2}) == 3);
  }
  return 0;
}
