#include <cassert>
#include <memory>
#include <vector>

using std::unique_ptr, std::vector;

struct ListNode {
  unique_ptr<ListNode> next;
  int val{};

  ListNode() = default;
  explicit ListNode(const int x) : val(x) {}
};

// auto reverse_list(ListNode* head) -> ListNode* {
//   ListNode* prev = nullptr;
//   auto* current = head;

//   while (current != nullptr) {
//     auto next = current->next;
//     current->next = prev;
//     prev = current;
//     current = next;
//   }

//   return prev;
// }

auto reverse_list(unique_ptr<ListNode> head) {
  unique_ptr<ListNode> prev = nullptr;
  unique_ptr<ListNode> curr = std::move(head);

  while (curr != nullptr) {
    unique_ptr<ListNode> next = std::move(curr->next);
    curr->next = std::move(prev);
    prev = std::move(curr);
    curr = std::move(next);
  }

  return prev;
}

auto build_list(const vector<int>& vals) -> unique_ptr<ListNode> {
  if (vals.empty()) {
    return nullptr;
  }

  auto head = std::make_unique<ListNode>(vals.at(0));
  auto* current = head.get();

  for (size_t i{1}; i < vals.size(); ++i) {
    current->next = std::make_unique<ListNode>(vals[i]);
    current = current->next.get();
  }

  return head;
}

auto into_vector(unique_ptr<ListNode> head) {
  vector<int> data;

  while (head != nullptr) {
    data.push_back(head->val);
    head = std::move(head->next);
  }

  return data;
}

auto main() -> int {
  {
    auto data = build_list({1, 2, 3, 4, 5});
    auto reversed = reverse_list(std::move(data));
    auto result_vec = into_vector(std::move(reversed));
    const auto expected = vector<int>{5, 4, 3, 2, 1};
    assert(result_vec == expected);
  }
  return 0;
}
