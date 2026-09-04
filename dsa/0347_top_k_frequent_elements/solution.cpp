#include <algorithm>
#include <cassert>
#include <queue>
#include <unordered_map>
#include <vector>

using std::priority_queue, std::vector, std::unordered_map, std::greater;
using std::ranges::sort;
using frequency_pair = std::pair<int, int>;

vector<int> top_k_frequent(const vector<int>& nums, const size_t k) {
  unordered_map<int, int> frequency_map;  // K: number, V: frequency
  frequency_map.reserve(nums.size());

  for (const auto& num : nums) {
    frequency_map[num]++;
  }

  priority_queue<frequency_pair, vector<frequency_pair>, greater<>> min_heap;

  for (const auto& it : frequency_map) {
    min_heap.emplace(it.second, it.first);  // {frequency, element}

    if (min_heap.size() > k) {
      min_heap.pop();
    }
  }

  vector<int> result;
  result.reserve(k);

  while (!min_heap.empty()) {
    result.emplace_back(min_heap.top().second);
    min_heap.pop();
  }

  return result;
}

int main() {
  {
    auto result = top_k_frequent({1, 1, 1, 2, 2, 3}, 2);
    const vector<int> expected = {1, 2};
    sort(result);

    assert(result.size() == expected.size());
    assert(result == expected);
  }
  {
    const auto result = top_k_frequent({1}, 1);
    const vector<int> expected = {1};
    assert(result.size() == expected.size());
    assert(result == expected);
  }
  {
    auto result = top_k_frequent({1, 2, 1, 2, 1, 2, 3, 1, 3, 2}, 2);
    const vector<int> expected = {1, 2};
    sort(result);
    assert(result.size() == expected.size());
    assert(result == expected);
  }
}
