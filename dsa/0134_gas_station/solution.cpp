// Problem: https://leetcode.com/problems/gas-station/
#include <cassert>
#include <vector>

using std::vector;

auto can_complete_circuit(const vector<int>& gas, const vector<int>& cost) -> int {
  // thought process:
  // We need to return the the index of the starting gas station if we can go clockwise
  // and return to the same station and -1 if we can not do so.
  // So essentially, we are given a list of gas stations and a list of gas cost(amount of gas
  // required to go to the next gas station).
  // We need to find out the index of the gas station at which we can start our journey and end our
  // journey
  //
  // How do we do that?
  // One approach is treating every index as the starting position and checking if we can get
  // back to the same index after clockwise rotation. The first index which does that is the return
  // index.
  //
  // Here, the base case seems to be -1 - "return -1 if all of the above fails"
  // There seems to be only one right index or none at all.
  // Now, how do we check if we can start the journey at a given index?
  // If the fuel we gain from gas[i] >= cost[i], then we can safely proceed to use that index
  // and test out if it works. If it does not, we search further in the gas array. If the array's
  // end is met, we can return -1. If an index is found which allows a full circle, we return that
  // index.
  //
  // What would be the condition which keeps track of the circle?
  // We need something like -
  // for i in range(n):
  // if (does_clockwise_rotation(i)):
  // return i
  //
  // return -1
  //
  // How would the helper function handle things?
  // We will be given an index as an input. We need to check first if at all
  // it can go to the next index of the given array. if not, early return false.
  // If it can, we check if it can keep going to the next index and return true if it lands there
  //

  int total{};
  int tank{};
  size_t start{};

  for (size_t i{}; i < gas.size(); i++) {
    const auto net = gas[i] - cost[i];
    total += net;
    tank += net;

    if (tank < 0) {
      start = i + 1;
      tank = 0;
    }
  }

  return total < 0 ? -1 : static_cast<int>(start);
}

int main() {
  {
    // LeetCode example 1 -> station 3 is the only valid start.
    const vector<int> gas{1, 2, 3, 4, 5};
    const vector<int> cost{3, 4, 5, 1, 2};
    assert(can_complete_circuit(gas, cost) == 3);
  }
  {
    // LeetCode example 2 -> total gas (9) < total cost (10).
    const vector<int> gas{2, 3, 4};
    const vector<int> cost{3, 4, 3};
    assert(can_complete_circuit(gas, cost) == -1);
  }
  {
    // A single profitable station.
    const vector<int> gas{5};
    const vector<int> cost{4};
    assert(can_complete_circuit(gas, cost) == 0);
  }
  {
    // A single unprofitable station.
    const vector<int> gas{4};
    const vector<int> cost{5};
    assert(can_complete_circuit(gas, cost) == -1);
  }
  return 0;
}
