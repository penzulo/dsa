#include <array>
#include <cassert>
#include <unordered_set>
#include <vector>

using std::array, std::vector, std::size_t;
using char_set = std::unordered_set<char>;
using board_type = vector<vector<char>>;

constexpr unsigned n_sudoku{9};

bool is_valid_sudoku(const board_type& board) {
  array<char_set, n_sudoku> rows;
  array<char_set, n_sudoku> cols;
  array<char_set, n_sudoku> boxes;

  for (size_t r{}; r < n_sudoku; ++r) {
    for (size_t c{}; c < n_sudoku; ++c) {
      const auto val = board[r][c];

      if (val == '.') {
        continue;
      }

      const size_t box_index = ((r / 3) * 3) + (c / 3);

      // This is the interesting bit. The insert fails if there already
      // exists the same number. std::unordered_set::insert returns a std::pair
      // object where in the first item is an iterator and the second is a boolean
      // to represent if the insert was successful. If it fails, we know that we
      // were trying to add a duplicate element so we can safely return false.
      if (!rows[r].insert(val).second || !cols[c].insert(val).second ||
          !boxes[box_index].insert(val).second) {
        return false;
      }
    }
  }

  return true;
}

auto make_empty_board() { return board_type(n_sudoku, vector<char>(n_sudoku, '.')); }

int main() {
  // Valid, partially filled board from the problem's example.
  {
    const board_type board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                              {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                              {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                              {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                              {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                              {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                              {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                              {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                              {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    assert(is_valid_sudoku(board));
  }

  // Fully solved valid sudoku.
  {
    const board_type board = {{'1', '2', '3', '4', '5', '6', '7', '8', '9'},
                              {'4', '5', '6', '7', '8', '9', '1', '2', '3'},
                              {'7', '8', '9', '1', '2', '3', '4', '5', '6'},
                              {'2', '3', '1', '5', '6', '4', '8', '9', '7'},
                              {'5', '6', '4', '8', '9', '7', '2', '3', '1'},
                              {'8', '9', '7', '2', '3', '1', '5', '6', '4'},
                              {'3', '1', '2', '6', '4', '5', '9', '7', '8'},
                              {'6', '4', '5', '9', '7', '8', '3', '1', '2'},
                              {'9', '7', '8', '3', '1', '2', '6', '4', '5'}};
    assert(is_valid_sudoku(board));
  }

  // Empty board is trivially valid.
  {
    const board_type board = make_empty_board();
    assert(is_valid_sudoku(board));
  }

  // A single digit anywhere is valid.
  {
    auto board = make_empty_board();
    board[4][4] = '5';
    assert(is_valid_sudoku(board));
  }

  // Duplicate digit in a row.
  {
    auto board = make_empty_board();
    board[3][0] = '1';
    board[3][4] = '1';
    assert(!is_valid_sudoku(board));
  }

  // Duplicate digit in a column.
  {
    auto board = make_empty_board();
    board[0][2] = '1';
    board[8][2] = '1';
    assert(!is_valid_sudoku(board));
  }

  // Duplicate digit inside a single 3x3 box.
  {
    auto board = make_empty_board();
    board[1][1] = '5';
    board[2][2] = '5';
    assert(!is_valid_sudoku(board));
  }

  return 0;
}
