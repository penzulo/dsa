#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

using std::vector;

auto min_eating_speed(const vector<int>& piles, const int h) -> int {
  auto left{1};
  auto right{*std::ranges::max_element(piles)};
  auto min_k{right};

  while (left <= right) {
    const auto k = (left + right) / 2;
    const auto hours = std::accumulate(
        piles.begin(), piles.end(), int64_t{0},
        [k](const int64_t total, const int pile) { return total + ((pile + k - 1) / k); });

    if (hours <= h) {
      min_k = std::min(min_k, k);
      right = k - 1;
    } else {
      left = k + 1;
    }
  }

  return min_k;
}

int main() {
  {
    const auto data = {3, 6, 7, 11};
    const auto result = min_eating_speed(data, 8);
    assert(result == 4);
  }
  {
    const auto data = {30, 11, 23, 4, 20};
    const auto result = min_eating_speed(data, 5);
    assert(result == 30);
  }
  {
    const auto data = {30, 11, 23, 4, 20};
    const auto result = min_eating_speed(data, 6);
    assert(result == 23);
  }
  {
    const auto data = {805306368, 805306368, 805306368};
    const auto result = min_eating_speed(data, 1000000000);
    assert(result == 3);
  }
  return 0;
}
