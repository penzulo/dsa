#include <stack>
#include <vector>

using std::vector, std::stack, std::size_t;

auto final_prices(const vector<int>& prices) -> vector<int> {
  auto result = prices;
  stack<int> monotonic_stack;

  for (size_t i{}; i < prices.size(); ++i) {
    while (!monotonic_stack.empty() && prices[monotonic_stack.top()] >= prices[i]) {
      const auto index = monotonic_stack.top();
      monotonic_stack.pop();
      result[index] -= prices[i];
    }

    monotonic_stack.emplace(i);
  }

  return result;
}

int main() { return 0; }
