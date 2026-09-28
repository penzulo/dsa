#include <array>
#include <bitset>
#include <cassert>
#include <vector>

using board_type = std::vector<std::vector<char>>;
using std::array, std::size_t;

constexpr unsigned n_sudoku{9};

bool is_valid_sudoku(const board_type& board) {
  array<std::bitset<n_sudoku>, n_sudoku> rows;
  array<std::bitset<n_sudoku>, n_sudoku> cols;
  array<std::bitset<n_sudoku>, n_sudoku> boxes;

  for (size_t row{}; row < n_sudoku; ++row) {
    for (size_t col{}; col < n_sudoku; ++col) {
      const auto val = board[row][col];

      if (val == '.') {
        continue;
      }

      const auto digit = static_cast<size_t>(val - '1');
      const auto box = ((row / 3) * 3) + (col / 3);

      // If any of this returns true, this means that `val` is already seen.
      if (rows[row].test(digit) || cols[col].test(digit) || boxes[box].test(digit)) {
        return false;
      }

      rows[row].set(digit);
      cols[col].set(digit);
      boxes[box].set(digit);
    }
  }

  return true;
}

auto make_empty_board() { return board_type(n_sudoku, std::vector<char>(n_sudoku, '.')); }

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
