#include <cassert>
#include <vector>

using std::vector;
using input_t = vector<vector<int>>;

auto search_matrix(const input_t& matrix, const int target) -> bool {
  // So the brute force way is this -
  for (const auto& row : matrix) {
    for (const auto num : row) {
      if (num == target) {
        return true;
      }
    }
  }

  return false;  // End case after best-effort
}

int main() {
  {
    const input_t data = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    const int target = 3;
    assert(search_matrix(data, target));
  }
  return 0;
}
