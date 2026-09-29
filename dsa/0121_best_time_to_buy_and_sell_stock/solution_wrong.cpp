#include <algorithm>
#include <cassert>
#include <vector>

using std::vector, std::size_t;

auto max_profit(const vector<int>& prices) -> int {
  size_t left{};
  size_t right{prices.size() - 1};

  int max_profit{};

  while (left < right) {
    if (prices[left] > prices[right]) {
      ++left;
    } else {
      max_profit = std::max(max_profit, prices[right] - prices[left]);
      if (prices[left + 1] < prices[left]) {
        ++left;
      } else {
        --right;
      }
    }
  }

  return max_profit;
}

int main() {
  {
    const auto result = max_profit({7, 1, 5, 3, 6, 4});
    const auto expected = 5;
    assert(result == expected);
  }
  {
    const auto result = max_profit({7, 6, 4, 3, 1});
    const auto expected = 0;
    assert(result == expected);
  }
  {
    const auto result = max_profit({2, 1, 4});
    const auto expected = 3;
    assert(result == expected);
  }
  return 0;
}
