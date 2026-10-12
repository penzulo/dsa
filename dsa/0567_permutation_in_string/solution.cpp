// Problem: https://leetcode.com/problems/permutation-in-string/

#include <array>
#include <cassert>
#include <string>

using std::string, std::array;

constexpr size_t n_alphabet{26};

auto check_inclusion(const string& s1, const string& s2) -> bool {
  if (s1.size() > s2.size()) {
    return false;
  }

  array<int, n_alphabet> freq_s1{};
  for (const char c : s1) {
    ++freq_s1.at(static_cast<size_t>(c - 'a'));
  }

  for (size_t i{}; i <= s2.size() - s1.size(); ++i) {
    array<int, n_alphabet> freq_s2{};
    for (size_t j{}; j < s1.size(); ++j) {
      ++freq_s2.at(static_cast<size_t>(s2.at(i + j) - 'a'));
    }

    if (freq_s2 == freq_s1) {
      return true;
    }
  }

  return false;
}

int main() {
  {
    const string s1{"ab"};
    const string s2{"eidbaooo"};
    assert(check_inclusion(s1, s2));
  }
  {
    const string s1{"ab"};
    const string s2{"eidboaoo"};
    assert(!check_inclusion(s1, s2));
  }

  return 0;
}
