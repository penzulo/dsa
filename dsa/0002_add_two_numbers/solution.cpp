/**
 * Problem URL: https://leetcode.com/problems/add-two-numbers/
 */

#include <cassert>
#include <print>
#include <vector>

constexpr int base{10};

struct ListNode {
  int data{};
  ListNode* next{nullptr};

  ListNode() = default;
  explicit ListNode(int val) : data{val} {}
  ListNode(const int val, ListNode* next_node) : data{val}, next{next_node} {}
};

ListNode* add_two_numbers(ListNode* list1, ListNode* list2) {
  int carry{};
  ListNode result;
  ListNode* current = &result;

  while (list1 != nullptr || list2 != nullptr || carry != 0) {
    const int a = (list1 != nullptr) ? list1->data : 0;
    const int b = (list2 != nullptr) ? list2->data : 0;

    const int sum = a + b + carry;
    carry = sum / base;
    const int digit = sum % base;

    current->next = new ListNode(digit);
    current = current->next;

    if (list1 != nullptr) {
      list1 = list1->next;
    }
    if (list2 != nullptr) {
      list2 = list2->next;
    }
  }

  return result.next;
}

ListNode* build_list(const std::vector<int>& nums) {
  ListNode dummy;
  ListNode* current = &dummy;
  for (const int& num : nums) {
    current->next = new ListNode(num);
    current = current->next;
  }
  return dummy.next;
}

std::vector<int> to_vector(ListNode* node) {
  std::vector<int> result;
  while (node != nullptr) {
    result.emplace_back(node->data);
    node = node->next;
  }
  return result;
}

void delete_list(ListNode* head) {
  while (head != nullptr) {
    ListNode* next = head->next;
    delete head;
    head = next;
  }
}

int main() {
  {
    auto* l1 = build_list({2, 4, 3});
    auto* l2 = build_list({5, 6, 4});
    auto* result = add_two_numbers(l1, l2);
    std::vector<int> expected{7, 0, 8};
    assert(to_vector(result) == expected);

    delete_list(l1);
    delete_list(l2);
    delete_list(result);
  }

  std::println("all tests passed!");
}
