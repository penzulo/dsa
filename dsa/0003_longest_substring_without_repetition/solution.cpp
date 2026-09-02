#include <algorithm>
#include <cassert>
#include <print>
#include <string>
#include <vector>

constexpr int unique_vals{256};

size_t length_of_longest_substring(const std::string& s) {
  std::vector<size_t> last_seen(unique_vals, std::string::npos);
  size_t max_length{};
  size_t left{};

  for (size_t right = 0; right < s.size(); right++) {
    auto c = static_cast<unsigned char>(s[right]);

    if (last_seen[c] >= left && last_seen[c] != std::string::npos) {
      left = last_seen[c] + 1;
    }

    last_seen[c] = right;
    max_length = std::max(max_length, right - left + 1);
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
  return 0;
}
