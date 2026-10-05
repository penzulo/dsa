#include <bitset>
#include <cassert>
#include <string>
#include <utility>

using std::bitset, std::string, std::size_t;

constexpr size_t n_alphabet{26};

auto repeated_character(const string& s) -> char {
  std::bitset<n_alphabet> bset;
  for (const char c : s) {
    const auto index = static_cast<size_t>(c - 'a');

    if (bset.test(index)) {
      return c;
    }

    bset.set(index);
  }
  std::unreachable();
}

int main() {
  {
    const string s{"abccbaacz"};
    assert(repeated_character(s) == 'c');
  }
  {
    const string s{"abcdd"};
    assert(repeated_character(s) == 'd');
  }

  return 0;
}
