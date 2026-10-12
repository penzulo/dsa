// Problem: https://leetcode.com/problems/linked-list-cycle/

#include <cassert>
#include <vector>

using std::vector;

struct ListNode {
  int val{};
  ListNode* next{};

  ListNode() = default;
  explicit ListNode(int x) : val(x) {}
};

auto has_cycle(const ListNode* head) -> bool {
  const auto* fast = head;
  const auto* slow = head;

  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      return true;
    }
  }

  return false;
}

auto build_list(const vector<int>& vals) -> ListNode* {
  if (vals.empty()) {
    return nullptr;
  }

  auto* head = new ListNode(vals.at(0));
  auto* current = head;

  for (size_t i{1}; i < vals.size(); ++i) {
    current->next = new ListNode(vals.at(i));
    current = current->next;
  }

  return head;
}

// Builds a list from `vals` and, when `pos >= 0`, forms a cycle by linking
// the tail back to the node at index `pos` (the LeetCode `pos` convention).
// Note: `pos` must be a valid index into `vals`.
auto build_cycle_list(const vector<int>& vals, const int pos) -> ListNode* {
  auto* head = build_list(vals);
  if (head == nullptr || pos < 0) {
    return head;
  }

  auto* entry = head;
  for (int i{}; i < pos; ++i) {
    entry = entry->next;
  }

  auto* tail = head;
  while (tail->next != nullptr) {
    tail = tail->next;
  }
  tail->next = entry;

  return head;
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
    // Empty list has no cycle.
    ListNode* head = build_list({});
    assert(!has_cycle(head));
  }
  {
    // Single node without a self-loop.
    ListNode* head = build_list({1});
    assert(!has_cycle(head));
    delete head;
  }
  {
    // Example 3: single node, no cycle.
    ListNode* head = build_cycle_list({1}, -1);
    assert(!has_cycle(head));
    delete head;
  }
  {
    // Single node with a self-loop.
    ListNode* head = build_cycle_list({1}, 0);
    assert(has_cycle(head));
  }
  {
    // Two nodes, acyclic.
    ListNode* head = build_list({1, 2});
    assert(!has_cycle(head));
    delete_list(head);
  }
  {
    // Example 2: two nodes, head points back to each other forming a cycle.
    ListNode* head = build_cycle_list({1, 2}, 0);
    assert(has_cycle(head));
  }
  {
    // Example 1: tail points back to index 1 (value 2) -> cycle exists.
    ListNode* head = build_cycle_list({3, 2, 0, -4}, 1);
    assert(has_cycle(head));
  }
  {
    // A whole chain that feeds back to its middle (index 2).
    ListNode* head = build_cycle_list({1, 2, 3, 4, 5}, 2);
    assert(has_cycle(head));
  }
  {
    // Longer acyclic list.
    ListNode* head = build_list({1, 2, 3, 4, 5});
    assert(!has_cycle(head));
    delete_list(head);
  }

  return 0;
}
