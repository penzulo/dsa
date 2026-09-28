#include <cassert>
#include <stack>

struct MinStack {
  std::stack<int> base;
  std::stack<int> min_stack;

  MinStack() = default;

  auto push(const int value) {
    base.emplace(value);

    if (min_stack.empty() || value < min_stack.top()) {
      min_stack.emplace(value);  // update the minimum value
    } else {
      min_stack.emplace(min_stack.top());  // add the current min element to the top
    }
  }

  auto pop() {
    base.pop();
    min_stack.pop();
  }

  [[nodiscard]] auto top() const noexcept { return base.top(); }
  [[nodiscard]] auto get_min() const -> int { return min_stack.top(); }
};

int main() {
  {
    // Example from the problem statement.
    MinStack stack;
    stack.push(-2);
    stack.push(0);
    stack.push(-3);
    assert(stack.get_min() == -3);
    stack.pop();
    assert(stack.top() == 0);
    assert(stack.get_min() == -2);
  }
  {
    // Minimum must survive pushes of larger values on top.
    MinStack stack;
    stack.push(3);
    stack.push(5);
    stack.push(4);
    assert(stack.get_min() == 3);
    stack.pop();
    assert(stack.get_min() == 3);
  }
  {
    // Duplicate minimum values are tracked independently.
    MinStack stack;
    stack.push(1);
    stack.push(1);
    assert(stack.get_min() == 1);
    stack.pop();
    assert(stack.get_min() == 1);
  }
  {
    // New minimum, then pops expose the previous minimum.
    MinStack stack;
    stack.push(5);
    stack.push(1);
    stack.push(2);
    assert(stack.get_min() == 1);
    stack.pop();
    stack.pop();
    assert(stack.top() == 5);
    assert(stack.get_min() == 5);
  }
  {
    // Single element stack.
    MinStack stack;
    stack.push(42);
    assert(stack.top() == 42);
    assert(stack.get_min() == 42);
    stack.pop();
  }

  return 0;
}
