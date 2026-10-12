// Problem: https://leetcode.com/problems/insert-delete-getrandom-o1/

#include <algorithm>
#include <cassert>
#include <random>
#include <unordered_map>
#include <utility>
#include <vector>

struct RandomizedSet {
  std::vector<int> store;
  std::unordered_map<int, size_t> reg;
  std::mt19937 rng{std::random_device{}()};

  RandomizedSet() = default;

  auto insert(const int val) -> bool {
    if (reg.emplace(val, store.size()).second) {
      store.emplace_back(val);
      return true;
    }

    return false;
  }

  auto remove(const int val) -> bool {
    if (!reg.contains(val)) {
      return false;  // nothing to delete
    }

    const auto current_index = reg[val];
    const auto last_val = store.back();
    store[current_index] = last_val;
    reg[last_val] = current_index;
    store.pop_back();
    reg.erase(val);

    return true;
  }

  auto get_random() -> int {
    assert(!store.empty());
    std::uniform_int_distribution<size_t> dist(0, store.size() - 1);
    return store.at(dist(rng));
  }
};

template <typename T>
auto sorted_copy(std::vector<T> v) -> std::vector<T> {
  std::sort(v.begin(), v.end());
  return v;
}

int main() {
  {
    // First-time insert/remove, plus no-op duplicates.
    RandomizedSet r;
    assert(r.insert(1));
    assert(!r.insert(1));
    assert(r.remove(1));
    assert(!r.remove(1));
    assert(!r.remove(9));
  }
  {
    // Removing must update the moved element's registry entry, not erase it.
    // {1,2,3} -> remove(2) => store={1,3}, reg={1:0,3:1}; remove(3) must then
    // succeed. (With the erase(last_val) bug this second remove returns false.)
    RandomizedSet r;
    assert(r.insert(1));
    assert(r.insert(2));
    assert(r.insert(3));
    assert(r.remove(2));
    assert(r.remove(3));
    assert(!r.remove(2));
    const auto copy = sorted_copy(r.store);
    assert(copy == std::vector<int>{1});
    assert(r.reg.size() == 1);
  }
  {
    // Reinsertion after removal.
    RandomizedSet r;
    assert(r.insert(7));
    assert(r.remove(7));
    assert(r.insert(7));
    const auto copy = sorted_copy(r.store);
    assert(copy == std::vector<int>{7});
  }
  {
    // get_random over a singleton always yields that value.
    RandomizedSet r;
    r.insert(42);
    for (int i{}; i < 32; ++i) {
      assert(r.get_random() == 42);
    }
  }
  {
    // After removals, get_random stays inside the current set.
    RandomizedSet r;
    r.insert(1);
    r.insert(2);
    r.insert(3);
    r.insert(4);
    r.remove(2);
    r.remove(4);
    for (int i{}; i < 32; ++i) {
      const int v = r.get_random();
      assert(v == 1 || v == 3);
    }
    assert(r.store.size() == 2);
    assert(r.reg.size() == r.store.size());
  }

  return 0;
}
