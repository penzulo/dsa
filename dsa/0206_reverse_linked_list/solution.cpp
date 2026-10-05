#include <cassert>
#include <vector>

using std::vector;

struct ListNode {
  ListNode* next{};
  int val{};

  ListNode() = default;
  explicit ListNode(const int x) : val(x) {}
};

auto reverse_list(ListNode* head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }

  auto* new_head = reverse_list(head->next);
  head->next->next = head;
  head->next = nullptr;

  return new_head;
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

auto into_vector(ListNode* head) {
  vector<int> data;

  while (head != nullptr) {
    data.push_back(head->val);
    head = head->next;
  }

  return data;
}

auto main() -> int {
  {
    auto* data = build_list({1, 2, 3, 4, 5});
    auto* reversed = reverse_list(data);
    auto result_vec = into_vector(reversed);
    const auto expected = vector<int>{5, 4, 3, 2, 1};
    assert(result_vec == expected);
  }
  return 0;
}
