// Problem: https://leetcode.com/problems/number-of-islands/
#include <array>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>

using std::vector, std::queue, std::array, std::pair;
using coord_t = pair<int, int>;

template <typename T>
using grid_t = vector<vector<T>>;

auto num_islands(const grid_t<char>& grid) -> int {
  if (grid.empty() || grid[0].empty()) {
    return 0;
  }

  const auto rows = grid.size();
  const auto cols = grid[0].size();

  grid_t<bool> visited(rows, vector<bool>(cols, false));

  constexpr array<int, 4> delta_r{-1, 1, 0, 0};  // Up, Down, Left, Right
  constexpr array<int, 4> delta_c{0, 0, -1, 1};  // Up, Down, Left, Right

  int islands{};

  for (size_t r{}; r < rows; ++r) {
    for (size_t c{}; c < cols; ++c) {
      // If it is water, or we've seen it, skip it.
      if (grid[r][c] != '1' || visited[r][c]) {
        continue;
      }

      // Here, it is an island and not visited before
      ++islands;

      // Now, we need to check it's neighbours (BFS)
      queue<coord_t> q;
      q.emplace(static_cast<int>(r), static_cast<int>(c));
      visited[r][c] = true;  // Set the current cell to be already visited

      while (!q.empty()) {
        const auto [current_r, current_c] = q.front();
        q.pop();

        // Check neighbours in each direction
        for (size_t d{}; d < delta_r.size(); ++d) {
          const auto new_row = current_r + delta_r[d];
          const auto new_col = current_c + delta_c[d];

          // Check if new co-ordinate is in bounds
          if (new_row < 0 || static_cast<size_t>(new_row) >= rows || new_col < 0 ||
              static_cast<size_t>(new_col) >= cols) {
            continue;  // skip if not in bounds
          }

          const auto row_idx = static_cast<size_t>(new_row);
          const auto col_idx = static_cast<size_t>(new_col);

          // Check if newly found neighbour is water or visited
          if (grid[row_idx][col_idx] != '1' || visited[row_idx][col_idx]) {
            continue;
          }

          // Here, we can enqueue the neighbour and mark it visited.
          visited[row_idx][col_idx] = true;
          q.emplace(new_row, new_col);
        }
      }
    }
  }

  return islands;
}

int main() {
  {
    // LeetCode example 1 -> a single island.
    const grid_t<char> grid{{'1', '1', '1', '1', '0'},
                            {'1', '1', '0', '1', '0'},
                            {'1', '1', '0', '0', '0'},
                            {'0', '0', '0', '0', '0'}};
    assert(num_islands(grid) == 1);
  }
  {
    // LeetCode example 2 -> three separate islands.
    const grid_t<char> grid{{'1', '1', '0', '0', '0'},
                            {'1', '1', '0', '0', '0'},
                            {'0', '0', '1', '0', '0'},
                            {'0', '0', '0', '1', '1'}};
    assert(num_islands(grid) == 3);
  }
  {
    // Empty grid.
    const grid_t<char> grid{};
    assert(num_islands(grid) == 0);
  }
  {
    // A single water cell.
    const grid_t<char> grid{{'0'}};
    assert(num_islands(grid) == 0);
  }
  {
    // A single land cell.
    const grid_t<char> grid{{'1'}};
    assert(num_islands(grid) == 1);
  }
  {
    // Diagonals are not connected -- only the 4 orthogonal directions count.
    const grid_t<char> grid{{'1', '0', '0'}, {'0', '1', '0'}, {'0', '0', '1'}};
    assert(num_islands(grid) == 3);
  }
  {
    // An island that wraps a water cell still counts once.
    const grid_t<char> grid{{'1', '1', '1'}, {'1', '0', '1'}, {'1', '1', '1'}};
    assert(num_islands(grid) == 1);
  }
  return 0;
}
