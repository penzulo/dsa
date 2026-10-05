#include <cassert>
#include <stack>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using std::vector, std::string, std::string_view;

auto is_operator(const string_view token) -> bool {
  return token == "+" || token == "-" || token == "*" || token == "/";
}

auto math_operation(const int left, const string_view op, const int right) -> int {
  switch (op.front()) {
    case '+': return left + right;
    case '-': return left - right;
    case '*': return left * right;
    case '/': return left / right;
    default: std::unreachable();
  }
}

auto eval_prn(const vector<string>& strs) -> int {
  std::stack<int> stack;

  for (const auto& str : strs) {
    if (!is_operator(str)) {
      stack.push(std::stoi(str));
      continue;
    }

    const auto right = stack.top();
    stack.pop();

    const auto left = stack.top();
    stack.pop();

    stack.push(math_operation(left, str, right));
  }

  return stack.top();
}

int main() {
  {
    // Example 1 from the problem statement: (2 + 1) * 3.
    const auto result = eval_prn({"2", "1", "+", "3", "*"});
    const auto expected{9};
    assert(result == expected);
  }
  {
    // Example 2 from the problem statement: 4 + (13 / 5).
    const auto result = eval_prn({"4", "13", "5", "/", "+"});
    const auto expected{6};
    assert(result == expected);
  }
  {
    // Example 3 from the problem statement: a long mixed expression.
    const auto result =
        eval_prn({"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"});
    const auto expected{22};
    assert(result == expected);
  }
  {
    // A single operand.
    const auto result = eval_prn({"5"});
    const auto expected{5};
    assert(result == expected);
  }
  {
    // A single negative operand: "-3" is a number, not the minus operator.
    const auto result = eval_prn({"-3"});
    const auto expected{-3};
    assert(result == expected);
  }
  {
    // Subtraction is left-to-right: 5 - 3.
    const auto result = eval_prn({"5", "3", "-"});
    const auto expected{2};
    assert(result == expected);
  }
  {
    // Operand order matters for subtraction: 3 - 5 is not 5 - 3.
    const auto result = eval_prn({"3", "5", "-"});
    const auto expected{-2};
    assert(result == expected);
  }
  {
    // Division truncates toward zero: 7 / 2.
    const auto result = eval_prn({"7", "2", "/"});
    const auto expected{3};
    assert(result == expected);
  }
  {
    // Negative division also truncates toward zero: -7 / 2.
    const auto result = eval_prn({"-7", "2", "/"});
    const auto expected{-3};
    assert(result == expected);
  }
  {
    // Independent subexpressions combined at the end: (1 + 2) * (3 + 4).
    const auto result = eval_prn({"1", "2", "+", "3", "4", "+", "*"});
    const auto expected{21};
    assert(result == expected);
  }
  {
    // A right-heavy chain: 3 - (11 + 5).
    const auto result = eval_prn({"3", "11", "5", "+", "-"});
    const auto expected{-13};
    assert(result == expected);
  }
  {
    // A nested composition: (5 + ((1 + 2) * 4)) - 3.
    const auto result = eval_prn({"5", "1", "2", "+", "4", "*", "+", "3", "-"});
    const auto expected{14};
    assert(result == expected);
  }
  {
    // Multiplication before addition: (2 * 3) + 4.
    const auto result = eval_prn({"2", "3", "*", "4", "+"});
    const auto expected{10};
    assert(result == expected);
  }

  return 0;
}
