#include <algorithm>
#include <cassert>
#include <climits>
#include <vector>

using std::vector;

auto max_profit(const vector<int>& prices) -> int {
  int min_price{INT_MAX};
  int max_profit{};

  for (const auto price : prices) {
    min_price = std::min(min_price, price);
    max_profit = std::max(max_profit, price - min_price);
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
