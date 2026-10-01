#include <cassert>
#include <vector>

using std::vector, std::size_t;

auto final_prices(const vector<int>& prices) -> vector<int> {
  vector<int> result(prices.size());

  for (size_t i{}; i < prices.size(); ++i) {
    // Determine minimum index of smaller or equal element to current
    // price. Subtract it's value from the current price and emplace in
    // result at index i
    size_t next{i + 1};
    while (next < prices.size() && prices[next] > prices[i]) {
      ++next;
    }

    result[i] = prices[i] - (next >= prices.size() ? 0 : prices[next]);
  }

  return result;
}

int main() { return 0; }
