#include <cassert>
#include <vector>

using std::vector;
using input_t = vector<vector<int>>;

auto search_matrix(const input_t& matrix, const int target) -> bool {
  // A matrix is m * n where m is the number of rows and n is the
  // number of columns
  size_t m{matrix.size()};
  size_t n{matrix[0].size()};

  size_t left{};
  size_t right{(m * n)};

  while (left < right) {
    const auto mid = left + ((right - left) / 2);  // The row to check
    // mid / n gives the row and mid % n gives the column
    const auto current = matrix[mid / n][mid % n];

    if (current > target) {
      right = mid;
    } else if (current < target) {
      left = mid + 1;
    } else {
      return true;
    }
  }

  return false;  // base case
}

int main() {
  {
    const input_t data = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    const int target = 3;
    assert(search_matrix(data, target));
  }
  {
    const input_t data = {{1}};
    const int target = 0;
    assert(!search_matrix(data, target));
  }
  return 0;
}
