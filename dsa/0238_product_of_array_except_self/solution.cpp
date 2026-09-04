#include <cassert>
#include <vector>

using std::vector;

vector<int> product_except_self(const vector<int>& nums) {
  vector<int> result(nums.size(), 1);
  int prefix{1};
  int postfix{1};

  for (size_t i{0}; i < nums.size(); i++) {
    result[i] = prefix;
    prefix *= nums[i];
  }

  for (int i = static_cast<int>(nums.size() - 1); i >= 0; i--) {
    const auto index = static_cast<size_t>(i);
    result[index] *= postfix;
    postfix *= nums[index];
  }

  return result;
}

int main() {
  {
    const auto result = product_except_self({1, 2, 3, 4});
    const vector<int> expected{24, 12, 8, 6};

    assert(result.size() == expected.size());
    assert(result == expected);
  }
  {
    const auto result = product_except_self({-1, 1, 0, -3, 3});
    const vector<int> expected{0, 0, 9, 0, 0};

    assert(result.size() == expected.size());
    assert(result == expected);
  }

  return 0;
}
