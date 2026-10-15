// Problem: https://leetcode.com/problems/climbing-stairs/
#include <cassert>

auto climb_stairs(const int n) -> int {
  // Thought process
  // What are we supposed to return? The number of ways we can reach the top.
  // Here, n represent the last step.
  // Can n be zero? no. n is guarenteed to be between 1 and 45
  //
  // We need to store the maximum number of ways and return the the count.
  // What is the brute force solution? To check every combination
  // Let the brute force solution be.
  int first{1};
  int second{1};

  for (int i{}; i < n - 1; i++) {
    const auto temp = first;
    first = first + second;
    second = temp;
  }

  return first;
}

int main() {
  {
    // One step -> a single way.
    assert(climb_stairs(1) == 1);
  }
  {
    // LeetCode example 1 -> two steps (1 + 1 or 2).
    assert(climb_stairs(2) == 2);
  }
  {
    // LeetCode example 2.
    assert(climb_stairs(3) == 3);
  }
  {
    // The sequence continues as the Fibonacci numbers.
    assert(climb_stairs(4) == 5);
    assert(climb_stairs(5) == 8);
  }
  {
    // The largest input LeetCode allows; still fits a 32-bit int.
    assert(climb_stairs(45) == 1836311903);
  }
  return 0;
}
