// Problem: https://leetcode.com/problems/jump-game/
#include <cassert>
#include <vector>

using std::vector;

auto can_jump(const vector<int>& nums) -> bool {
  // Thought process:
  // We need to return a boolean: whether we can reach the last index (nums.back()) or not.
  // nums[i] is between 0 and 10^5 inclusive.
  // The length of the given array will be at least 1.
  // From what I understand, the problem states that every nums[i] represents the maximum
  // jump length from that position. Your jump length can be between 0 and nums[i] inclusive.
  //
  // What questions can I ask?
  // 1. From the back of the array, is there a a jump which reaches the last index?
  // 2. What would be the brute force approach?
  // 3. Is there a way to calculate if the current nums[i] can be reached by previous elements?
  // 4. Can I jump less than my maximum?
  //
  // Bias for solution -
  // I think that calculating minimum jumps between to adjacent numbers is the way we can check
  // if nums[i - 1] can even reach nums[i] and then we can just do that iteratively until we reach
  // nums[n - 1]
  //
  // Testing this out with an example -
  // [3, 2, 2, 0, 4]
  // starting at three, we can jump to the second 2
  // from the second two, we can jump to 4 which is the last element. This breaks the adjacent
  // validation rule I was going for.
  //
  // What we know -
  // The jump length at nums[i] can be between nums[i] and 0
  // How can we make use of that information?
  // Am I asking the right questions?
  // 0 is the only jump length which breaks our logic.
  // At each point we can ask these questions -
  // 1. Can my previous element reach me be it the maximum jump or the minimum?
  // 2. Can my current element reach the next element in any way?
  // If both the conditions are not true, we can return false.
  //
  // What if the question I can ask is this -
  // What size of the jump do I need to make to reach a non-zero
  // element?
  //
  // This approach passes 110/178 tests but seems more appropriate and breaks down an
  // array to isolate it's individual element to check the maximum reach of that element
  // and if any of the elements reach the end or not.
  size_t target{nums.size() - 1};  // index of the target element

  for (size_t i{nums.size() - 1}; i > 0; i--) {
    const size_t index = i - 1;

    if (index + static_cast<size_t>(nums[index]) >= target) {
      target = index;
    }
  }

  return target == 0;
}

int main() {
  {
    // LeetCode example 1.
    const vector<int> nums{2, 3, 1, 1, 4};
    assert(can_jump(nums));
  }
  {
    // LeetCode example 2 -> stuck on the 0 at index 3.
    const vector<int> nums{3, 2, 1, 0, 4};
    assert(!can_jump(nums));
  }
  {
    // A single element is already the last index.
    const vector<int> nums{0};
    assert(can_jump(nums));
  }
  {
    // A single element with a jump budget.
    const vector<int> nums{1};
    assert(can_jump(nums));
  }
  {
    // Cannot leave the first position.
    const vector<int> nums{0, 1};
    assert(!can_jump(nums));
  }
  {
    // Jump straight over the zeros to the end.
    const vector<int> nums{2, 0, 0};
    assert(can_jump(nums));
  }
  {
    // Landing on the 0 at index 1 strands us before the last index.
    const vector<int> nums{1, 0, 1};
    assert(!can_jump(nums));
  }
  return 0;
}

// Passes 162 of 178 tests
// const auto last_index = nums.size() - 1;
//         for (size_t i{}; i < nums.size(); i++) {
//             if (i == last_index || i + nums[i] >= last_index) {
//                 // This means that we're already at the last number or we can reach the last
//                 number. return true;
//             }

//             // Check if the current element can reach the next element.
//             if (nums[i] == 0) {
//                 return false;
//             }
//         }

//         return false;
