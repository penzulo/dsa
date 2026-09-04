#include <cassert>
#include <string>

// @note this works for certain tests but is a bad approach as
// sums of different characters might be the same which is unexpected
// behaviour.
bool is_anagram(const std::string& s1, const std::string& s2) {
  if (s1.size() != s2.size()) {
    return false;
  }

  unsigned int sum_s1{};
  unsigned int sum_s2{};

  for (size_t i{}; i < s1.size(); i++) {
    sum_s1 += static_cast<unsigned int>(s1[i]);
    sum_s2 += static_cast<unsigned int>(s2[i]);
  }

  return sum_s1 == sum_s2;
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
