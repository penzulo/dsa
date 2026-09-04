#include <algorithm>
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

constexpr int alphabet_n{26};

using std::vector, std::string, std::unordered_map;
using result_t = vector<vector<string>>;

result_t group_anagrams(const vector<string>& strs) {
  unordered_map<string, vector<string>> map;

  for (const string& str : strs) {
    string key(alphabet_n, 0);

    for (const auto& c : str) {
      const auto index = static_cast<size_t>(c - 'a');
      key[index]++;
    }

    map[key].emplace_back(str);
  }

  result_t result;
  result.reserve(map.size());

  for (const auto& pair : map) {
    result.emplace_back(pair.second);
  }

  return result;
}

result_t normalize(result_t result) {
  for (auto& group : result) {
    std::ranges::sort(group);
  }

  std::ranges::sort(result);

  return result;
}

int main() {
  {
    vector<string> data = {"eat", "tea", "tan", "ate", "nat", "bat"};
    const result_t result = group_anagrams(data);
    const result_t expected = {{"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}};

    assert(result.size() == 3);
    assert(normalize(result) == normalize(expected));
  }
  {
    vector<string> data = {""};
    const result_t result = group_anagrams(data);
    const result_t expected = {{""}};

    assert(result.size() == 1);
    assert(normalize(result) == normalize(expected));
  }
  {
    vector<string> data = {"a"};
    const result_t result = group_anagrams(data);
    const result_t expected = {{"a"}};

    assert(result.size() == 1);
    assert(normalize(result) == normalize(expected));
  }

  return 0;
}
