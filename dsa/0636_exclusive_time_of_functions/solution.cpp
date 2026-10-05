#include <cassert>
#include <stack>
#include <string>
#include <vector>

using std::vector, std::string, std::stack, std::size_t;

auto exclusive_time(const int n, const vector<string>& logs) -> vector<int> {
  vector<int> result(static_cast<size_t>(n));
  stack<int> function_stack;
  int elapsed_time{};

  // A "start" log pushes the new function id. If a function was already on
  // the stack, it was interrupted, so credit it with the time elapsed since
  // the previous event before starting the new call.
  //
  // An "end" log credits the function on top of the stack with the elapsed
  // time (inclusive of the end timestamp, hence the +1) and pops it.
  for (const auto& log : logs) {
    const auto first_colon = log.find(':');
    const auto second_colon = log.find(':', first_colon + 1);

    const auto function_id = std::stoi(log.substr(0, first_colon));
    const auto event = log.substr(first_colon + 1, second_colon - first_colon - 1);
    const auto timestamp = std::stoi(log.substr(second_colon + 1));

    if (event == "start") {
      if (!function_stack.empty()) {
        result[static_cast<size_t>(function_stack.top())] += timestamp - elapsed_time;
      }

      function_stack.push(function_id);
      elapsed_time = timestamp;
    } else {
      result[static_cast<size_t>(function_stack.top())] += timestamp - elapsed_time + 1;
      function_stack.pop();
      elapsed_time = timestamp + 1;
    }
  }

  return result;
}

int main() {
  {
    // Example 1 from the problem statement.
    const vector<string> logs{"0:start:0", "1:start:2", "1:end:5", "0:end:6"};
    const auto result = exclusive_time(2, logs);
    const vector<int> expected{3, 4};
    assert(result == expected);
  }
  {
    // Example 2 from the problem statement: nested same-id calls.
    const vector<string> logs{"0:start:0", "0:start:2", "0:end:5",
                              "0:start:6", "0:end:6",   "0:end:7"};
    const auto result = exclusive_time(1, logs);
    const vector<int> expected{8};
    assert(result == expected);
  }
  {
    // Start and end in the same timestamp.
    const vector<string> logs{"0:start:0", "0:end:0"};
    const auto result = exclusive_time(1, logs);
    const vector<int> expected{1};
    assert(result == expected);
  }
  {
    // Two functions run one after the other, never overlapping.
    const vector<string> logs{"0:start:0", "0:end:5", "1:start:6", "1:end:6"};
    const auto result = exclusive_time(2, logs);
    const vector<int> expected{6, 1};
    assert(result == expected);
  }
  {
    // Three functions nested to depth three.
    const vector<string> logs{"0:start:0", "1:start:2", "2:start:3",
                              "2:end:4",   "1:end:5",   "0:end:6"};
    const auto result = exclusive_time(3, logs);
    const vector<int> expected{3, 2, 2};
    assert(result == expected);
  }
  {
    // Timestamps do not have to start at zero.
    const vector<string> logs{"0:start:5", "1:start:7", "1:end:7", "0:end:10"};
    const auto result = exclusive_time(2, logs);
    const vector<int> expected{5, 1};
    assert(result == expected);
  }
  {
    // A single timestamp-wide call later in the timeline.
    const vector<string> logs{"0:start:3", "0:end:3"};
    const auto result = exclusive_time(1, logs);
    const vector<int> expected{1};
    assert(result == expected);
  }
  {
    // A long single call.
    const vector<string> logs{"0:start:0", "0:end:100"};
    const auto result = exclusive_time(1, logs);
    const vector<int> expected{101};
    assert(result == expected);
  }

  return 0;
}
