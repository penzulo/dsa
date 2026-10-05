#include <algorithm>
#include <cassert>
#include <ranges>
#include <utility>
#include <vector>

using std::vector, std::pair, std::ranges::views::zip;

auto car_fleet(const vector<int>& position, const int target, const vector<int>& speed) -> int {
  vector<float> stack;
  vector<std::pair<int, int>> pairs;
  pairs.reserve(position.size());

  for (const auto [p, s] : zip(position, speed)) {
    pairs.emplace_back(p, s);
  }

  std::ranges::sort(pairs);

  for (const auto [pos, sp] : pairs) {
    const auto time = static_cast<float>(target - pos) / static_cast<float>(sp);
    while (!stack.empty() && time >= stack.back()) {
      stack.pop_back();
    }
    stack.push_back(time);
  }

  return static_cast<int>(stack.size());
}

int main() {
  {
    const vector<int> position{10, 8, 0, 5, 3};
    const vector<int> speed{2, 4, 1, 1, 3};
    const auto result = car_fleet(position, 12, speed);
    assert(result == 3);
  }
  {
    const vector<int> position{3};
    const vector<int> speed{3};
    const auto result = car_fleet(position, 10, speed);
    assert(result == 1);
  }
  {
    const vector<int> position{0, 2, 4};
    const vector<int> speed{4, 2, 1};
    const auto result = car_fleet(position, 100, speed);
    assert(result == 1);
  }

  return 0;
}
