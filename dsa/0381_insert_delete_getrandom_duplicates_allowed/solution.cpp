// Problem: https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/

#include <cassert>
#include <random>
#include <unordered_map>
#include <vector>

struct RandomizedCollection {
  std::vector<int> store;
  // K: number, V: list of indices
  std::unordered_map<int, std::vector<size_t>> reg;
  std::mt19937 rng{std::random_device{}()};

  auto insert(const int val) -> bool {
    // Got right: the vector + map(value->indices) layout. Missed: the boolean
    // is inverted -- it must be true when the value was *not* already present.
    const auto has_value = reg.contains(val);
    reg[val].push_back(store.size());
    store.push_back(val);

    return !has_value;
  }

  auto remove(const int val) -> bool {
    // Got right: the swap-with-back O(1) removal shape and the index-list idea.
    // Missed: reg[last_val] is in *insertion order*, so the moved last element
    // is the entry equal to the old back index -- not reg[last_val].back().
    if (!reg.contains(val)) {
      return false;
    }

    const auto last_seen = reg[val].back();
    const auto last_val = store.back();
    const auto old_back = store.size() - 1;
    store[last_seen] = last_val;

    for (auto& idx : reg[last_val]) {
      if (idx == old_back) {
        idx = last_seen;
        break;
      }
    }

    store.pop_back();
    reg[val].pop_back();
    if (reg[val].empty()) {
      reg.erase(val);
    }

    return true;
  }

  auto get_random() -> int {
    // Got right: non-empty guard and uniform sampling over store.
    assert(!store.empty());
    std::uniform_int_distribution<size_t> dist(0, store.size() - 1);
    return store.at(dist(rng));
  }
};

int main() {
  {
    // insert returns true for a new value, false when it already exists.
    RandomizedCollection r;
    assert(r.insert(10));
    assert(!r.insert(10));  // duplicate, still stored twice
    assert(r.insert(20));
    assert(r.store.size() == 3);
    assert(r.reg[10].size() == 2);
    assert(r.reg[20].size() == 1);
  }
  {
    // remove on an absent value returns false.
    RandomizedCollection r;
    r.insert(1);
    assert(!r.remove(2));
  }
  {
    // The failing sequence: duplicates plus interleaved removes of a moved value.
    RandomizedCollection r;
    r.insert(10);
    r.insert(10);
    r.insert(20);
    r.insert(20);
    r.insert(30);
    r.insert(30);
    assert(r.remove(10));
    assert(r.remove(20));
    assert(r.remove(20));
    assert(r.remove(10));
    assert(r.remove(30));
    r.insert(40);
    assert(r.remove(30));
    assert(!r.remove(30));

    // Only 40 survives, and reg/store stay consistent.
    assert(r.store.size() == 1);
    assert(r.store[0] == 40);
    assert(r.reg.size() == 1);
    assert(r.reg[40].size() == 1);
    assert(r.reg[40][0] == 0);
    for (int i{}; i < 16; ++i) {
      assert(r.get_random() == 40);
    }
  }
  {
    // Removing the last element (val == last_val) keeps bookkeeping sane.
    RandomizedCollection r;
    r.insert(5);
    r.insert(6);
    assert(r.remove(6));
    assert(r.store.size() == 1);
    assert(r.store[0] == 5);
    assert(r.reg.size() == 1);
    for (int i{}; i < 16; ++i) {
      assert(r.get_random() == 5);
    }
  }

  return 0;
}
