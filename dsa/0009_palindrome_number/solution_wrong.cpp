#include <cassert>

constexpr int base{10};

// There is a problem with this solution and it is regarding
// integer overflow therefore, reversing the entire integer
// will go beyond the range of 4 bytes and cause `UB`.
bool is_palindrome(const int x) {
  if (x < 0) {
    return false;
  }

  int num{x};
  int result{};

  while (num != 0) {
    result = (base * result) + (num % base);
    num /= base;
  }

  return result == x;
}

int main() {
  {
    assert(is_palindrome(121));
    assert(is_palindrome(12321));
    assert(!is_palindrome(6767));
    assert(!is_palindrome(10));
    assert(!is_palindrome(-121));
  }
  return 0;
}
