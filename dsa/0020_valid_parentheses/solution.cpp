#include <cassert>
#include <stack>
#include <unordered_map>

using std::string;

auto is_valid(const string& s) -> bool {
  std::stack<char> stack;
  std::unordered_map<char, char> pair_map = {
      {')', '('},
      {']', '['},
      {'}', '{'},
  };

  for (const auto c : s) {
    if (pair_map.contains(c)) {
      if (!stack.empty() && stack.top() == pair_map[c]) {
        stack.pop();
      } else {
        return false;
      }
    } else {
      stack.emplace(c);
    }
  }

  // At the end, the stack should be empty. If it is not, then we have
  // an incomplete sequence.
  return stack.empty();
}

int main() {
  {
    assert(is_valid("()"));
    assert(is_valid("()[]{}"));
    assert(!is_valid("(]"));
    assert(is_valid("([])"));
    assert(!is_valid("([)]"));
  }
  return 0;
}
