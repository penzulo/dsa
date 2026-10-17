// Problem: https://leetcode.com/problems/rotting-oranges/
#include <array>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>

using std::vector, std::array, std::queue, std::pair;
using coord_t = pair<int, int>;

template <typename T>
using grid_t = vector<vector<T>>;

auto oranges_rotting(grid_t<int>& grid) -> int {
  /*
   * Thought Process:
   * We need to return the number of minutes that must elapse in order
   * to turn a fresh orange into a rotten one and -1 if is impossible.
   * IT IS NOT GUARENTEED THAT THERE MIGHT BE AT LEAST A SINGLE ROTTEN ORANGE
   * We need to check if the grid has any fresh oranges at all too.
   * We need to check if ALL the fresh oranges have rotten. If a single fresh orange remains,
   * we return -1.
   *
   * Here, a minute might just be a single iteration.
   * What we can do -
   * Iterate through the grid.
   * For each cell, if the cell is a fresh orange or a is an empty cell, skip
   * If the cell is a rotten orange, push it to the queue and maintain a counter of iterations
   * each iteration, increment that counter. If the counter is 0, that means that no rotten orange
   * is found so no adjacent fresh orange will be affected. Hence we return -1.
   */
  if (grid.empty() || grid[0].empty()) {
    return 0;
  }

  const auto rows = grid.size();
  const auto cols = grid[0].size();

  // We still need the direction arrays
  constexpr array<int, 4> delta_r{-1, 1, 0, 0};  // Up, Down, Left, Right
  constexpr array<int, 4> delta_c{0, 0, -1, 1};  // Up, Down, Left, Right

  queue<coord_t> q;
  int fresh_oranges{};

  for (size_t r{}; r < rows; r++) {
    for (size_t c{}; c < cols; c++) {
      if (grid[r][c] == 2) {
        q.emplace(static_cast<int>(r), static_cast<int>(c));
      } else if (grid[r][c] == 1) {
        fresh_oranges++;
      }
    }
  }

  int minutes{};

  while (!q.empty() && fresh_oranges > 0) {
    const auto level_size = q.size();

    for (size_t i{}; i < level_size; ++i) {
      const auto [current_r, current_c] = q.front();
      q.pop();

      for (size_t d{}; d < delta_r.size(); d++) {
        const auto new_r = current_r + delta_r[d];
        const auto new_c = current_c + delta_c[d];

        if (new_r < 0 || static_cast<size_t>(new_r) >= rows || new_c < 0 ||
            static_cast<size_t>(new_c) >= cols) {
          continue;
        }

        const auto row_idx = static_cast<size_t>(new_r);
        const auto col_idx = static_cast<size_t>(new_c);

        if (grid[row_idx][col_idx] != 1) {
          continue;
        }

        // Here, the current co-ordinate represents a fresh orange
        // spread the rot
        grid[row_idx][col_idx] = 2;
        --fresh_oranges;
        q.emplace(new_r, new_c);
      }
    }

    minutes++;
  }

  // Now we have the number of fresh oranges.
  // We need to check if after rotting, is the count of
  // fresh oranges 0? If yes, then all the oranges have rotten. we return the number of iterations
  // if not, we return -1 as it is impossible to rot all oranges.
  return fresh_oranges == 0 ? minutes : -1;
}

int main() {
  {
    // LeetCode example 1 -> every orange rots in 4 minutes.
    grid_t<int> grid{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    assert(oranges_rotting(grid) == 4);
  }
  {
    // LeetCode example 2 -> one orange is unreachable.
    grid_t<int> grid{{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
    assert(oranges_rotting(grid) == -1);
  }
  {
    // LeetCode example 3 -> no fresh oranges.
    grid_t<int> grid{{0, 2}};
    assert(oranges_rotting(grid) == 0);
  }
  {
    // Fresh oranges but no rotten source -> impossible.
    grid_t<int> grid{{1, 1}, {1, 1}};
    assert(oranges_rotting(grid) == -1);
  }
  {
    // All empty cells -> nothing to rot.
    grid_t<int> grid{{0, 0}, {0, 0}};
    assert(oranges_rotting(grid) == 0);
  }
  {
    // A single rotten orange -> 0 minutes.
    grid_t<int> grid{{2}};
    assert(oranges_rotting(grid) == 0);
  }
  {
    // Spread along a row: one minute per hop.
    grid_t<int> grid{{2, 1, 1, 1}};
    assert(oranges_rotting(grid) == 3);
  }
  {
    // Two rotten sources spread in parallel: the middle orange takes 2 minutes.
    grid_t<int> grid{{2, 1, 1, 1, 2}};
    assert(oranges_rotting(grid) == 2);
  }
  {
    // Empty grid.
    grid_t<int> grid{};
    assert(oranges_rotting(grid) == 0);
  }
  return 0;
}
