#include <cassert>
#include <string>

using std::string, std::size_t;

auto remove_outer_brackets(const string& s) {
  string result;
  size_t count{};

  for (const char c : s) {
    if (c == ')') {
      --count;
    }

    if (count != 0) {
      result += c;
    }

    if (c == '(') {
      ++count;
    }
  }

  return result;
}

int main() { return 0; }
