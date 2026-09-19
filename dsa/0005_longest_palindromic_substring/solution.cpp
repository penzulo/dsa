#include <algorithm>
#include <cassert>
#include <string>

using std::string;
using index_t = string::difference_type;

size_t expand_around_center(index_t left, index_t right, const string& text) {
  while (left >= 0 && right < static_cast<index_t>(text.size()) &&
         text[left] == text[right]) {
    --left;
    ++right;
  }

  return static_cast<size_t>(right - left - 1);
}

std::string longest_palindrome(const std::string& s) {
  if (s.empty()) {
    return {};
  }

  index_t best_start{};
  size_t best_length{};

  for (index_t i{}; i < static_cast<index_t>(s.size()); ++i) {
    const auto odd_length = expand_around_center(i, i, s);
    const auto even_length = expand_around_center(i, i + 1, s);
    const auto length = std::max(odd_length, even_length);

    if (length > best_length) {
      best_length = length;

      // For both odd and even length palindromes, this gives
      // the leftmost index of the palindrome.
      best_start = i - static_cast<index_t>((length - 1) / 2);
    }
  }

  return s.substr(static_cast<size_t>(best_start), best_length);
}

int main() {
  {
    // testing odd lengths
    const auto result = longest_palindrome("babad");
    assert(result.size() == 3);
    assert(result == "bab" || result == "aba");
  }

  {
    // testing even lengths
    const auto result = longest_palindrome("cbbd");
    assert(result == "bb");
  }

  {
    // testing no palindrome over 1
    const auto result = longest_palindrome("ac");
    assert(result.size() == 1);
    assert(result == "a" || result == "c");
  }

  {
    // testing empty string
    const auto result = longest_palindrome("");
    assert(result.empty());
  }

  return 0;
}
