#include <cassert>
#include <memory>
#include <vector>

using std::unique_ptr;

struct ListNode {
  ListNode* next{};
  int val{};

  ListNode() = default;
  explicit ListNode(const int k) : val(k) {}
};

auto merge_two_lists(ListNode* list1, ListNode* list2) -> ListNode* {
  if (list1 == nullptr) {
    return list2;
  }
  if (list2 == nullptr) {
    return list2;
  }

  if (list1->val <= list2->val) {
    list1->next = merge_two_lists(list1->next, list2);
    return list1;
  }
  list2->next = merge_two_lists(list2->next, list1);
  return list2;
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

std::vector<int> to_vector(const ListNode* node) {
  std::vector<int> result;
  while (node != nullptr) {
    result.emplace_back(node->val);
    node = node->next;
  }
  return result;
}

void delete_list(const ListNode* head) {
  while (head != nullptr) {
    ListNode* next = head->next;
    delete head;
    head = next;
  }
}

int main() {
  {
    // Example 1 from the problem statement.
    ListNode* l1 = build_list({1, 2, 4});
    ListNode* l2 = build_list({1, 3, 4});
    ListNode* result = merge_two_lists(l1, l2);
    const std::vector<int> expected{1, 1, 2, 3, 4, 4};
    assert(to_vector(result) == expected);
    delete_list(result);
  }
  {
    // Both lists empty.
    ListNode* l1 = build_list({});
    ListNode* l2 = build_list({});
    ListNode* result = merge_two_lists(l1, l2);
    const std::vector<int> expected{};
    assert(to_vector(result) == expected);
    delete_list(result);
  }
  {
    // One list empty, the other a singleton.
    ListNode* l1 = build_list({});
    ListNode* l2 = build_list({0});
    ListNode* result = merge_two_lists(l1, l2);
    const std::vector<int> expected{0};
    assert(to_vector(result) == expected);
    delete_list(result);
  }
  {
    // Different lengths: shorter one exhausts first.
    ListNode* l1 = build_list({5});
    ListNode* l2 = build_list({1, 2, 4});
    ListNode* result = merge_two_lists(l1, l2);
    const std::vector<int> expected{1, 2, 4, 5};
    assert(to_vector(result) == expected);
    delete_list(result);
  }
  {
    // Every value in list1 comes before list2.
    ListNode* l1 = build_list({1, 2, 3});
    ListNode* l2 = build_list({4, 5, 6});
    ListNode* result = merge_two_lists(l1, l2);
    const std::vector<int> expected{1, 2, 3, 4, 5, 6};
    assert(to_vector(result) == expected);
    delete_list(result);
  }
  {
    // Every value in list2 comes before list1.
    ListNode* l1 = build_list({4, 5, 6});
    ListNode* l2 = build_list({1, 2, 3});
    ListNode* result = merge_two_lists(l1, l2);
    const std::vector<int> expected{1, 2, 3, 4, 5, 6};
    assert(to_vector(result) == expected);
    delete_list(result);
  }
  {
    // Fully interleaved duplicates.
    ListNode* l1 = build_list({1, 3, 5});
    ListNode* l2 = build_list({1, 3, 5});
    ListNode* result = merge_two_lists(l1, l2);
    const std::vector<int> expected{1, 1, 3, 3, 5, 5};
    assert(to_vector(result) == expected);
    delete_list(result);
  }
  {
    // Negative values mixed in.
    ListNode* l1 = build_list({-5, -1, 0});
    ListNode* l2 = build_list({-3, 2});
    ListNode* result = merge_two_lists(l1, l2);
    const std::vector<int> expected{-5, -3, -1, 0, 2};
    assert(to_vector(result) == expected);
    delete_list(result);
  }
  {
    // One node each.
    ListNode* l1 = build_list({1});
    ListNode* l2 = build_list({2});
    ListNode* result = merge_two_lists(l1, l2);
    const std::vector<int> expected{1, 2};
    assert(to_vector(result) == expected);
    delete_list(result);
  }
  {
    // First list null, second single node.
    ListNode* l1 = build_list({});
    ListNode* l2 = build_list({7});
    ListNode* result = merge_two_lists(l1, l2);
    const std::vector<int> expected{7};
    assert(to_vector(result) == expected);
    delete_list(result);
  }

  return 0;
}
