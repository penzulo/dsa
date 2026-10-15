// Problem: https://leetcode.com/problems/max-area-of-island/
#include <algorithm>
#include <array>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>

using std::vector, std::array, std::queue, std::pair;
using coord_t = pair<int, int>;

template <typename T>
using grid_t = vector<vector<T>>;

auto max_area_of_island(const vector<vector<int>>& grid) -> int {
  /*
   * Thought process -
   * There needs to be a variable to store the largest length of an island seen so far.
   * That variable needs to be initialized to zero. Follows `return 0 if no island is found` rule
   * by returning it directly.
   * We still need a visited array so as to not visit the same co-ordinate and process it again.
   * We start by checking every cell,
   * - if the cell has water or has been visited, we skip it.
   * - if the the cell contains land, we keep an area counter.
   * - increment the area counter every time we add it's neighbours to the queue and set them as
   * visited.
   * - update max area - `std::max(max_area, current_area)`
   */
  int max_area{};

  const auto rows = grid.size();
  const auto cols = grid[0].size();

  grid_t<bool> visited(rows, vector<bool>(cols, false));  // initialize boolean grid

  constexpr array<int, 4> delta_row{-1, 1, 0, 0};  // Up, Down, Left, Right
  constexpr array<int, 4> delta_col{0, 0, -1, 1};  // Up, Down, Left, Right

  for (size_t r{}; r < rows; ++r) {
    for (size_t c{}; c < cols; ++c) {
      if (grid[r][c] != 1 || visited[r][c]) {
        continue;
      }

      // Here, the co-ordinate is land and not visited.
      queue<coord_t> q;
      q.emplace(static_cast<int>(r), static_cast<int>(c));  // emplace current co-ordinate
      visited[r][c] = true;                                 // set current co-ordinate as visited
      auto current_area{1};

      while (!q.empty()) {
        const auto [current_r, current_c] = q.front();
        q.pop();

        // Check every neighbour
        for (size_t d{}; d < delta_row.size(); ++d) {
          const auto new_row = current_r + delta_row[d];
          const auto new_col = current_c + delta_col[d];

          // Check if new co-ordinate is in bounds
          if (new_row < 0 || static_cast<size_t>(new_row) >= rows || new_col < 0 ||
              static_cast<size_t>(new_col) >= cols) {
            continue;  // skip processing
          }

          const auto row_idx = static_cast<size_t>(new_row);
          const auto col_idx = static_cast<size_t>(new_col);

          // Check if the new co-ordinate is water or already visited
          if (grid[row_idx][col_idx] != 1 || visited[row_idx][col_idx]) {
            continue;  // skip processing
          }

          // Here, the new co-ordinate is not seen and is land.
          // How do we append to the area of this island?
          visited[row_idx][col_idx] = true;
          q.emplace(new_row, new_col);
          ++current_area;
        }
      }
      max_area = std::max(max_area, current_area);
    }
  }

  return max_area;
}

int main() {
  {
    // LeetCode example 1 -> the largest island has area 6.
    const vector<vector<int>> grid{
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};
    assert(max_area_of_island(grid) == 6);
  }
  {
    // LeetCode example 2 -> no land at all.
    const vector<vector<int>> grid{{0, 0, 0, 0, 0, 0, 0, 0}};
    assert(max_area_of_island(grid) == 0);
  }
  {
    // A single land cell.
    const vector<vector<int>> grid{{1}};
    assert(max_area_of_island(grid) == 1);
  }
  {
    // A single water cell.
    const vector<vector<int>> grid{{0}};
    assert(max_area_of_island(grid) == 0);
  }
  {
    // An L-shaped island (area 3) next to a 2x2 island (area 4): the larger wins.
    const vector<vector<int>> grid{{1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 1, 1}, {0, 0, 1, 1}};
    assert(max_area_of_island(grid) == 4);
  }
  {
    // An island enclosing a water cell is still a single (ring) island of area 8.
    const vector<vector<int>> grid{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    assert(max_area_of_island(grid) == 8);
  }
  return 0;
}
