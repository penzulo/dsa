#include <cassert>
#include <cctype>
#include <string>

using std::string, std::size_t;

auto is_palindrome(string& s) -> bool {
  // Remove/ignore Spaces and any character which is not in the alphabet
  std::erase_if(s, [](const char c) { return !std::isalnum(static_cast<unsigned char>(c)); });

  // Check if string is empty
  if (s.empty()) {
    return true;
  }

  size_t left{};
  size_t right{s.size() - 1};

  while (left < right) {
    if (std::tolower(static_cast<unsigned char>(s[left])) !=
        std::tolower(static_cast<unsigned char>(s[right]))) {
      return false;
    }
    ++left;
    --right;
  }

  return true;
}

int main() {
  {
    // Example from the problem statement.
    string input{"A man, a plan, a canal: Panama"};
    assert(is_palindrome(input));
  }
  {
    // Example from the problem statement (not a palindrome).
    string input{"race a car"};
    assert(!is_palindrome(input));
  }
  {
    // Example from the problem statement: filters down to an empty string.
    string input{" "};
    assert(is_palindrome(input));
  }
  {
    // Example from the problem statement: digits are significant.
    string input{"0P"};
    assert(!is_palindrome(input));
  }
  {
    // Empty input.
    string input{};
    assert(is_palindrome(input));
  }
  {
    // A single character.
    string input{"a"};
    assert(is_palindrome(input));
  }
  {
    // Punctuation only, filters to an empty string.
    string input{".,"};
    assert(is_palindrome(input));
  }
  {
    // Mixed case with an apostrophe and comma.
    string input{"Madam, I'm Adam"};
    assert(is_palindrome(input));
  }
  {
    // Palindrome phrase.
    string input{"A Santa at NASA"};
    assert(is_palindrome(input));
  }
  {
    // A longer classic palindrome.
    string input{"Able was I ere I saw Elba"};
    assert(is_palindrome(input));
  }
  {
    // Digits only.
    string input{"12321"};
    assert(is_palindrome(input));
  }
  {
    // Digits and letters that do not read the same backwards.
    string input{"1a2"};
    assert(!is_palindrome(input));
  }
  {
    // Repeated single character.
    string input{"aaaa"};
    assert(is_palindrome(input));
  }
  {
    // Two non-matching characters.
    string input{"ab"};
    assert(!is_palindrome(input));
  }

  return 0;
}