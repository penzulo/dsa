#include <cassert>
#include <stack>
#include <vector>

using std::vector, std::stack, std::size_t;

auto final_prices(const vector<int>& prices) -> vector<int> {
  auto result = prices;
  stack<int> monotonic_stack;

  for (size_t i{}; i < prices.size(); ++i) {
    while (!monotonic_stack.empty() &&
           prices[static_cast<size_t>(monotonic_stack.top())] >= prices[i]) {
      const auto index = monotonic_stack.top();
      monotonic_stack.pop();
      result[static_cast<size_t>(index)] -= prices[i];
    }

    monotonic_stack.emplace(static_cast<int>(i));
  }

  return result;
}

int main() {
  {
    // Example 1 from the problem statement.
    const auto result = final_prices({8, 4, 6, 2, 3});
    const vector<int> expected{4, 2, 4, 2, 3};
    assert(result == expected);
  }
  {
    // Example 2 from the problem statement.
    const auto result = final_prices({10, 1, 1, 6});
    const vector<int> expected{9, 0, 1, 6};
    assert(result == expected);
  }
  {
    // Strictly increasing: no discount applies anywhere.
    const auto result = final_prices({1, 2, 3, 4, 5});
    const vector<int> expected{1, 2, 3, 4, 5};
    assert(result == expected);
  }
  {
    // Strictly decreasing: each price minus the next one.
    const auto result = final_prices({5, 4, 3, 2, 1});
    const vector<int> expected{1, 1, 1, 1, 1};
    assert(result == expected);
  }
  {
    // A single price, never discounted.
    const auto result = final_prices({1});
    const vector<int> expected{1};
    assert(result == expected);
  }
  {
    // Repeated prices: the first two get the third as their discount.
    const auto result = final_prices({3, 3, 3});
    const vector<int> expected{0, 0, 3};
    assert(result == expected);
  }
  {
    // Discounts look ahead past larger prices.
    const auto result = final_prices({2, 3, 1, 5});
    const vector<int> expected{1, 2, 1, 5};
    assert(result == expected);
  }
  {
    // Empty input.
    const auto result = final_prices({});
    const vector<int> expected{};
    assert(result == expected);
  }

  return 0;
}