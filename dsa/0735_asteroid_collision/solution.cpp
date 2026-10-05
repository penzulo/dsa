#include <cassert>
#include <cstdlib>
#include <vector>

using std::vector, std::abs;

auto asteroid_collision(const vector<int>& asteroids) -> vector<int> {
  vector<int> result;

  for (const int current : asteroids) {
    bool is_alive{true};

    while (is_alive && !result.empty() && result.back() > 0 && current < 0) {
      // resolve collision
      if (abs(result.back()) == abs(current)) {
        result.pop_back();
        is_alive = false;
        // we don't add the current element
      } else if (abs(result.back()) > abs(current)) {
        is_alive = false;
      } else {
        result.pop_back();
      }
    }

    if (is_alive) {
      result.push_back(current);
    }
  }

  return result;
}

int main() {
  {
    // Example 1 from the problem statement.
    const auto result = asteroid_collision({5, 10, -5});
    const vector<int> expected{5, 10};
    assert(result == expected);
  }
  {
    // Example 2 from the problem statement: equal magnitudes destroy each other.
    const auto result = asteroid_collision({8, -8});
    const vector<int> expected{};
    assert(result == expected);
  }
  {
    // Example 3 from the problem statement: -5 beats 2, then loses to 10.
    const auto result = asteroid_collision({10, 2, -5});
    const vector<int> expected{10};
    assert(result == expected);
  }
  {
    // Example 4 from the problem statement: same direction, no collisions.
    const auto result = asteroid_collision({-2, -1, 1, 2});
    const vector<int> expected{-2, -1, 1, 2};
    assert(result == expected);
  }
  {
    // All moving right, nothing collides.
    const auto result = asteroid_collision({1, 2, 3});
    const vector<int> expected{1, 2, 3};
    assert(result == expected);
  }
  {
    // All moving left, nothing collides.
    const auto result = asteroid_collision({-1, -2, -3});
    const vector<int> expected{-1, -2, -3};
    assert(result == expected);
  }
  {
    // A single asteroid.
    const auto result = asteroid_collision({5});
    const vector<int> expected{5};
    assert(result == expected);
  }
  {
    // One big leftward asteroid destroys a whole chain on the way through.
    const auto result = asteroid_collision({1, 2, 3, -10});
    const vector<int> expected{-10};
    assert(result == expected);
  }
  {
    // A pair of explosions: (5, -5) then (10, -10).
    const auto result = asteroid_collision({10, 5, -5, -10});
    const vector<int> expected{};
    assert(result == expected);
  }
  {
    // -2 takes out the last 2, then -10 and 10 destroy each other.
    const auto result = asteroid_collision({10, 2, 2, -2, -10});
    const vector<int> expected{};
    assert(result == expected);
  }
  {
    // 5 and -5 annihilate in the middle; 3 on the right survives.
    const auto result = asteroid_collision({5, -5, 3});
    const vector<int> expected{3};
    assert(result == expected);
  }
  {
    // -3 smashes through 1, then keeps moving left past the left-moving asteroids.
    const auto result = asteroid_collision({-2, -1, 1, -3});
    const vector<int> expected{-2, -1, -3};
    assert(result == expected);
  }
  {
    // Empty input.
    const auto result = asteroid_collision({});
    const vector<int> expected{};
    assert(result == expected);
  }

  return 0;
}
