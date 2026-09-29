#include <cassert>
#include <cstddef>
#include <unordered_set>
#include <vector>

using std::vector, std::size_t;
using input_t = vector<vector<int>>;

auto is_magic_square(const input_t& grid, const size_t row, const size_t col) -> bool {
  std::unordered_set<int> values;

  // The 3x3 window must contain each digit 1..9 exactly once.
  for (size_t i{row}; i < row + 3; ++i) {
    for (size_t j{col}; j < col + 3; ++j) {
      const auto val = grid[i][j];
      if (values.contains(val) || 1 > val || val > 9) {
        return false;
      }
      values.insert(val);
    }
  }

  // Every row must add up to 15.
  for (size_t i{row}; i < row + 3; ++i) {
    if (grid[i][col] + grid[i][col + 1] + grid[i][col + 2] != 15) {
      return false;
    }
  }

  // Every column must add up to 15.
  for (size_t i{}; i < 3; ++i) {
    if (grid[row][i + col] + grid[row + 1][i + col] + grid[row + 2][i + col] != 15) {
      return false;
    }
  }

  // Both diagonals must add up to 15.
  const auto diagonal1{grid[row][col] + grid[row + 1][col + 1] + grid[row + 2][col + 2]};
  const auto diagonal2{grid[row][col + 2] + grid[row + 1][col + 1] + grid[row + 2][col]};

  return diagonal1 == 15 && diagonal2 == 15;
}

auto num_magic_squares(const input_t& grid) -> int {
  const auto rows = grid.size();
  const auto cols = grid[0].size();
  int count{};

  for (size_t row{}; row + 2 < rows; ++row) {
    for (size_t col{}; col + 2 < cols; ++col) {
      if (is_magic_square(grid, row, col)) {
        ++count;
      }
    }
  }

  return count;
}

// Hoists the asserts into a tiny helper so `main` stays flat and both
// functions keep a low cognitive-complexity score.
static void expect_magic_count(const input_t& grid, const int expected) {
  const auto result = num_magic_squares(grid);
  assert(result == expected);
}

int main() {
  // Example from the problem statement.
  expect_magic_count({{4, 3, 8, 4}, {9, 5, 1, 9}, {2, 7, 6, 2}}, 1);
  // The classic Lo Shu square.
  expect_magic_count({{4, 9, 2}, {3, 5, 7}, {8, 1, 6}}, 1);
  // A rotated/reflected orientation of Lo Shu.
  expect_magic_count({{8, 3, 4}, {1, 5, 9}, {6, 7, 2}}, 1);
  // Rows and columns all sum to 15, but the diagonals do not.
  expect_magic_count({{1, 5, 9}, {6, 7, 2}, {8, 3, 4}}, 0);
  // Distinct 1..9 with coincidental diagonals of 15, but broken rows.
  expect_magic_count({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 0);
  // Lo Shu tiled 2x2: only the four aligned 3x3 windows are magic.
  expect_magic_count({{4, 9, 2, 4, 9, 2},
                      {3, 5, 7, 3, 5, 7},
                      {8, 1, 6, 8, 1, 6},
                      {4, 9, 2, 4, 9, 2},
                      {3, 5, 7, 3, 5, 7},
                      {8, 1, 6, 8, 1, 6}},
                     4);
  // Values outside 1..9 are rejected immediately.
  expect_magic_count({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0);
  // Too narrow for any 3x3 window.
  expect_magic_count({{1, 2, 3}}, 0);
  // Too short for any 3x3 window.
  expect_magic_count({{1}, {2}, {3}}, 0);
  // Non-square grid: a single magic square in the top-left window.
  expect_magic_count({{4, 9, 2}, {3, 5, 7}, {8, 1, 6}, {4, 9, 2}}, 1);

  return 0;
}