#include <cassert>
#include <string>
#include <vector>

using std::vector, std::string;

string encode(const vector<string>& strs) {
  string result;
  for (const auto& str : strs) {
    const string token = std::to_string(str.size()) + "#" + str;
    result.append(token);
  }

  return result;
}

vector<string> decode(const string& encoded) {
  vector<string> result;
  size_t i{};

  while (i < encoded.size()) {
    size_t sep_index = encoded.find('#', i);  // find first '#' starting from i

    // @note stoul = "string to unsigned long"
    size_t length = std::stoul(encoded.substr(i, sep_index - i));

    i = sep_index + 1;

    result.emplace_back(encoded.substr(i, length));
    i += length;
  }

  return result;
}

int main() {
  {
    // @note encode basic case
    const string result = encode({"some", "string"});
    const string expected{"4#some6#string"};
    assert(result.size() == expected.size());
    assert(result == expected);
  }
  {
    // @note encode special case
    const string result = encode({"Hello#World", "a#b"});
    const string expected{"11#Hello#World3#a#b"};
    assert(result.size() == expected.size());
    assert(result == expected);
  }
  {
    // @note encode empty case
    const string result = encode({""});
    const string expected{"0#"};
    assert(result.size() == expected.size());
    assert(result == expected);
  }
  {
    // @note decode basic case
    const auto result = decode("4#some6#string");
    const vector<string> expected = {"some", "string"};
    assert(result.size() == expected.size());
  }
  {
    // @note decode special case
    const auto result = decode("11#Hello#World3#a#b");
    const vector<string> expected = {"Hello#World", "a#b"};
    assert(result.size() == expected.size());
  }

  return 0;
}
