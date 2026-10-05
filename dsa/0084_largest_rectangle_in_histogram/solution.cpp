#include <algorithm>
#include <cassert>
#include <ranges>
#include <vector>

using std::vector, std::pair, std::ranges::views::enumerate;

// auto largest_rectangle_area(const vector<int>& heights) -> int {
//   vector<pair<size_t, int>> stack;  // (index, value)
//   int best_area{};

//   for (const auto [i, height] : enumerate(heights)) {
//     const auto start = i;
//     while (!stack.empty() && stack.back().second > height) {
//       const auto [index, value] = stack.back();
//       stack.pop_back();

//       best_area = std::max<int>(best_area, static_cast<int>(value) * static_cast<int>(i -
//       index));
//     }
//   }

//   return best_area;
// }

int main() {
  // {
  //   const auto data = vector<int>{2, 1, 5, 6, 2, 3};
  //   const auto result = largest_rectangle_area(data);
  //   const auto expected = 10;
  //   assert(result == expected);
  // }
  // {
  //   const auto data = vector<int>{2, 4};
  //   const auto result = largest_rectangle_area(data);
  //   const auto expected = 4;
  //   assert(result == expected);
  // }
  return 0;
}
