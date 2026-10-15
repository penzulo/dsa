// Problem: https://leetcode.com/problems/merge-intervals/
#include <algorithm>
#include <cassert>
#include <vector>

using std::vector;
using interval_set = vector<vector<int>>;

auto merge(interval_set& intervals) -> interval_set {
  // Thought Process:
  // What do we need to return? a vector of non-overalpping / merged intervals
  // Can the vector be empty? No there will be at least one interval. If that's the
  // case, we can return it as it is.
  //
  // Can there be more than two overlapping intervals? The question does not say that such
  // an input WON'T be present so it's safe to assume the case.
  // Like - [[1, 5], [2, 3], [3, 5]]
  //
  // Each first element of an interval is the start of that interval and the second element
  // is the end element. We can maybe sort the intervals by it's start element to get a consistently
  // ordered interval set.
  // If the end of a previous interval and the start of a next interval are the same then they get
  // merged too.
  // We could probably solve this using a monotonic stack after sorting the array as we are only
  // concerned with comparing the prevoius interval with the current interval.
  //
  // Plan -
  // Create a stack.
  // For each interval in intervals:
  // if stack is not empty and stack.top()[1] >= interval[0],
  // stack.pop()
  // stack.push(merged_interval)
  // else
  // push the normal interval
  //
  // lastly, return the entire stack which contains merged intervals if they exist in the input
  // or overlapping intervals if the input is such.
  //

  std::ranges::sort(intervals);  // sort to get them local to each other
  interval_set stack;

  for (const auto& interval : intervals) {
    if (!stack.empty() && stack.back()[1] >= interval[0]) {
      const auto merged_interval =
          vector<int>{stack.back()[0], std::max(stack.back()[1], interval[1])};
      stack.pop_back();
      stack.push_back(merged_interval);
    } else {
      stack.push_back(interval);
    }
  }

  return stack;
}

// DRY RUN:
// [[1,3],[2,6],[8,10],[15,18]]
// interval = [1, 3] stack = []
// interval = [2, 6] stack = [[1, 3]]
// interval = [8, 10] stack = [[1, 6]]
// interval = [15, 18] stack = [[1, 6], [8, 10]]
// no interval stack = [[1, 6], [8, 10], [15, 18]]
// return stack

int main() {
  {
    // LeetCode example 1.
    interval_set intervals{{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    const interval_set expected{{1, 6}, {8, 10}, {15, 18}};
    assert(merge(intervals) == expected);
  }
  {
    // LeetCode example 2 -> touching intervals merge.
    interval_set intervals{{1, 4}, {4, 5}};
    const interval_set expected{{1, 5}};
    assert(merge(intervals) == expected);
  }
  {
    // A contained interval is absorbed by the wider one.
    interval_set intervals{{1, 4}, {2, 3}};
    const interval_set expected{{1, 4}};
    assert(merge(intervals) == expected);
  }
  {
    // Unsorted input is ordered first.
    interval_set intervals{{5, 6}, {1, 2}, {3, 4}};
    const interval_set expected{{1, 2}, {3, 4}, {5, 6}};
    assert(merge(intervals) == expected);
  }
  {
    // A single interval is returned unchanged.
    interval_set intervals{{1, 5}};
    const interval_set expected{{1, 5}};
    assert(merge(intervals) == expected);
  }
  return 0;
}
