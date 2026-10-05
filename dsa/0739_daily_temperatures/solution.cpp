#include <cassert>
#include <stack>
#include <vector>

using std::vector, std::size_t;

auto daily_temperatures(const vector<int>& temperatures) -> vector<int> {
  vector<int> result(temperatures.size());
  std::stack<size_t> stack;

  for (size_t i{}; i < temperatures.size(); ++i) {
    while (!stack.empty() && temperatures[stack.top()] < temperatures[i]) {
      const auto days = static_cast<int>(i - stack.top());
      result[stack.top()] = days;
      stack.pop();
    }

    stack.push(i);
  }

  return result;
}

int main() {
  {
    // Example 1 from the problem statement.
    const auto result = daily_temperatures({73, 74, 75, 71, 69, 72, 76, 73});
    const vector<int> expected{1, 1, 4, 2, 1, 1, 0, 0};
    assert(result == expected);
  }
  {
    // Example 2 from the problem statement.
    const auto result = daily_temperatures({30, 40, 50, 60});
    const vector<int> expected{1, 1, 1, 0};
    assert(result == expected);
  }
  {
    // Example 3 from the problem statement.
    const auto result = daily_temperatures({30, 60, 90});
    const vector<int> expected{1, 1, 0};
    assert(result == expected);
  }
  {
    // Strictly decreasing: no day is ever warmer.
    const auto result = daily_temperatures({90, 80, 70, 60});
    const vector<int> expected{0, 0, 0, 0};
    assert(result == expected);
  }
  {
    // Strictly increasing: each day sees the next one as warmer.
    const auto result = daily_temperatures({60, 70, 80, 90});
    const vector<int> expected{1, 1, 1, 0};
    assert(result == expected);
  }
  {
    // A single day.
    const auto result = daily_temperatures({70});
    const vector<int> expected{0};
    assert(result == expected);
  }
  {
    // Equal temperatures are not "warmer": nothing resolves.
    const auto result = daily_temperatures({70, 70, 70});
    const vector<int> expected{0, 0, 0};
    assert(result == expected);
  }
  {
    // Flat run ending in a spike: the spike resolves the whole run.
    const auto result = daily_temperatures({70, 70, 70, 80});
    const vector<int> expected{3, 2, 1, 0};
    assert(result == expected);
  }
  {
    // Two elements, warmer on the right.
    const auto result = daily_temperatures({30, 31});
    const vector<int> expected{1, 0};
    assert(result == expected);
  }
  {
    // A valley between two spikes.
    const auto result = daily_temperatures({31, 40, 38, 50});
    const vector<int> expected{1, 2, 1, 0};
    assert(result == expected);
  }
  {
    // Highest temperature first, never resolved.
    const auto result = daily_temperatures({99});
    const vector<int> expected{0};
    assert(result == expected);
  }
  {
    // Empty input.
    const auto result = daily_temperatures({});
    const vector<int> expected{};
    assert(result == expected);
  }

  return 0;
}
