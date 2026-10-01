#include <cassert>
#include <string>

using std::string, std::size_t;

auto remove_outer_brackets(const string& s) -> string {
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

int main() {
  {
    // Example 1 from the problem statement.
    const auto result = remove_outer_brackets("(()())(())");
    const string expected{"()()()"};
    assert(result == expected);
  }
  {
    // Example 2 from the problem statement.
    const auto result = remove_outer_brackets("(()())(())(()(()))");
    const string expected{"()()()()(())"};
    assert(result == expected);
  }
  {
    // Example 3 from the problem statement: two bare primitives.
    const auto result = remove_outer_brackets("()()");
    const string expected{""};
    assert(result == expected);
  }
  {
    // A single primitive leaves nothing behind.
    const auto result = remove_outer_brackets("()");
    const string expected{""};
    assert(result == expected);
  }
  {
    // One level of nesting inside the primitive.
    const auto result = remove_outer_brackets("(())");
    const string expected{"()"};
    assert(result == expected);
  }
  {
    // Primitives with different depths: (()()) and ().
    const auto result = remove_outer_brackets("(()())");
    const string expected{"()()"};
    assert(result == expected);
  }
  {
    // The whole string is a single deep primitive.
    const auto result = remove_outer_brackets("((()))");
    const string expected{"(())"};
    assert(result == expected);
  }
  {
    // Mixed primitive shapes.
    const auto result = remove_outer_brackets("(()(()))");
    const string expected{"()(())"};
    assert(result == expected);
  }
  {
    // Adjacent primitives of different depth.
    const auto result = remove_outer_brackets("()(())");
    const string expected{"()"};
    assert(result == expected);
  }

  return 0;
}