#include <algorithm>
#include <array>
#include <cassert>
#include <string>

constexpr int alphabet_n{26};

bool is_anagram(const std::string& s1, const std::string& s2) {
  if (s1.size() != s2.size()) {
    return false;
  }

  std::array<int, alphabet_n> frequency{};

  for (size_t i{}; i < s1.size(); i++) {
    const auto frequency_index_s1 = static_cast<size_t>(s1[i] - 'a');
    const auto frequency_index_s2 = static_cast<size_t>(s2[i] - 'a');

    frequency[frequency_index_s1]++;
    frequency[frequency_index_s2]--;
  }

  return std::ranges::all_of(frequency, [](int elem) { return elem == 0; });
}

int main() {
  {
    const auto result = is_anagram("anagram", "nagaram");
    assert(result);
  }
  {
    const auto result = is_anagram("rat", "car");
    assert(!result);
  }

  return 0;
}
