#include <cassert>
#include <string>

using std::string, std::size_t;

constexpr auto roman_value(const char c) noexcept -> int {
  switch (c) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default: return 0;
  }
}

auto roman_to_integer(const string& s) -> int {
  int result{};

  for (size_t i{}; i < s.size(); ++i) {
    const auto current = roman_value(s[i]);

    if (i + 1 < s.size() && current < roman_value(s[i + 1])) {
      result -= current;
    } else {
      result += current;
    }
  }

  return result;
}

int main() {
  {
    assert(roman_to_integer("III") == 3);
    assert(roman_to_integer("LVIII") == 58);
    assert(roman_to_integer("MCMXCIV") == 1994);
  }
  return 0;
}
