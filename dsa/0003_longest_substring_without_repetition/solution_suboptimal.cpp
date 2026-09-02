/**
 * Problem URL:
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * Visualisation: https://jr46mg.csb.app/
 */

#include <algorithm>
#include <cassert>
#include <print>
#include <string>
#include <unordered_map>

unsigned int length_of_longest_substring(const std::string& s) {
  std::unordered_map<char, unsigned int> frequency;
  unsigned int left = 0;
  unsigned int max_length = 0;

  for (size_t right = 0; right < s.length(); right++) {
    const char& current_char = s[right];
    frequency[current_char]++;  // Initializes with 0 if key does not exist

    while (frequency[current_char] > 1) {
      frequency[s[left]] -= 1;
      left++;
    }

    max_length = std::max<unsigned int>(max_length, right - left + 1);
  }

  return max_length;
}

int main() {
  {
    assert(length_of_longest_substring("abcabcbb") == 3);
    assert(length_of_longest_substring("pwwkew") == 3);
    assert(length_of_longest_substring("x") == 1);
  }

  {
    assert(length_of_longest_substring("bbbbb") == 1);
  }

  {
    assert(length_of_longest_substring("") == 0);
  }

  std::println("all tests passed!");
}
