// Problem: https://leetcode.com/problems/k-closest-points-to-origin/

#include <cassert>
#include <queue>
#include <utility>
#include <vector>

using std::vector, std::priority_queue, std::pair;
using input_t = vector<vector<int>>;

auto k_closest(const input_t& points, const size_t k) {
  // What we know -
  // 1. Each element in `points` is a vector of two elements (x and y)
  // 2. Arbitrary `k` which represent number of points closest to (0, 0)
  //
  // What I am thinking -
  // 1. We can store the distance of each point from origin in a heap
  // 2. The heap needs to be of size k
  // 3. The order of the result vector does not matter.
  // 4. The result vector is just the remaining elements in the heap
  //
  // What type does the heap need to be?
  // We need a max-heap as top k closest points will be stored.
  //
  // What should be stored inside the heap?
  // The min-heap must be sorted on the bases of the distance. We could use
  // a tuple[int, [x, y]] (distance and point itself) or we can just use a
  // tuple which stores the distance and the index of the point in the `points`
  // array
  priority_queue<pair<int, vector<int>>> max_heap;

  for (const auto& point : points) {
    const int x = point.at(0);
    const int y = point.at(1);
    const int distance = (x * x) + (y * y);

    max_heap.emplace(distance, point);

    if (max_heap.size() > k) {
      max_heap.pop();
    }
  }

  input_t answer;

  while (!max_heap.empty()) {
    answer.emplace_back(max_heap.top().second);
    max_heap.pop();
  }

  return answer;
}

int main() {
  {
    // k = 2 keeps both points; the result order is unspecified.
    const input_t points{{3, 3}, {-2, 4}};
    const auto out = k_closest(points, 2);
    assert(out.size() == 2);
    assert((out[0] == vector<int>{3, 3} || out[0] == vector<int>{-2, 4}));
    assert((out[1] == vector<int>{3, 3} || out[1] == vector<int>{-2, 4}));
    assert(out[0] != out[1]);
  }
  {
    // k = 1 keeps the closest point: (1,1) is distance 2, (2,2) is 8.
    const input_t points{{1, 1}, {2, 2}};
    const auto out = k_closest(points, 1);
    assert(out.size() == 1);
    assert(out[0] == vector<int>{1, 1});
  }
  {
    // Ties at distance 2: either point is a valid answer for k = 1.
    const input_t points{{1, 1}, {-1, -1}};
    const auto out = k_closest(points, 1);
    assert(out.size() == 1);
    assert((out[0] == vector<int>{1, 1} || out[0] == vector<int>{-1, -1}));
  }

  return 0;
}
