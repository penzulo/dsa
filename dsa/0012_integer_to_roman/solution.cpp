#include <array>
#include <cassert>
#include <string>
#include <utility>

using std::string, std::pair, std::array;

constexpr array roman_numerals{
    pair{1000, "M"}, pair{900, "CM"}, pair{500, "D"}, pair{400, "CD"}, pair{100, "C"},
    pair{90, "XC"},  pair{50, "L"},   pair{40, "XL"}, pair{10, "X"},   pair{9, "IX"},
    pair{5, "V"},    pair{4, "IV"},   pair{1, "I"},
};

auto to_roman(int num) -> string {
  string result;

  for (const auto& [value, symbol] : roman_numerals) {
    while (num >= value) {
      result += symbol;
      num -= value;
    }
  }

  return result;
}

auto main() -> int {
  {
    assert(to_roman(3749) == "MMMDCCXLIX");
    assert(to_roman(58) == "LVIII");
    assert(to_roman(1994) == "MCMXCIV");
  }
  return 0;
}
