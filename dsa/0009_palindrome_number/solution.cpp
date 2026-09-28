#include <cassert>

constexpr int base{10};

// There is a problem with this solution and it is regarding
// integer overflow therefore, reversing the entire integer
// will go beyond the range of 4 bytes and cause `UB`.
bool is_palindrome(int x) {
  if (x < 0 || (x % base == 0 && x != 0)) {
    return false;
  }

  int reversed{};

  while (x > reversed) {
    reversed = (reversed * base) + (x % base);
    x /= base;
  }

  return reversed == x || reversed / base == x;
}

int main() {
  {
    assert(is_palindrome(121));
    assert(is_palindrome(12321));
    assert(!is_palindrome(6767));
    assert(!is_palindrome(10));
    assert(!is_palindrome(-121));
    assert(!is_palindrome(2147483647));  // overflow case
  }
  return 0;
}
