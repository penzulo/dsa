// Problem: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/

#include <cassert>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

struct TreeNode {
  int val{};
  TreeNode* left{};
  TreeNode* right{};

  TreeNode() = default;
  explicit TreeNode(const int x) : val(x) {}
  TreeNode(TreeNode* l, const int x, TreeNode* r) : val(x), left(l), right(r) {}
};

namespace {

// Returns the LCA of the deepest leaves within `node`'s subtree, together with
// the subtree's height. A parent whose two subtrees are equally tall is itself
// the LCA; otherwise the answer is inherited from the taller subtree.
auto deepest_lca(TreeNode* node) -> std::pair<TreeNode*, int> {
  if (node == nullptr) {
    return {nullptr, 0};
  }

  const auto [left_lca, left_depth] = deepest_lca(node->left);
  const auto [right_lca, right_depth] = deepest_lca(node->right);

  if (left_depth == right_depth) {
    return {node, left_depth + 1};
  }

  if (left_depth > right_depth) {
    return {left_lca, left_depth + 1};
  }

  return {right_lca, right_depth + 1};
}

}  // namespace

auto lca_deepest_leaves(TreeNode* root) -> TreeNode* { return deepest_lca(root).first; }

auto build_tree(const std::vector<std::optional<int>>& vals) -> TreeNode* {
  if (vals.empty() || !vals.front().has_value()) {
    return nullptr;
  }

  auto* root = new TreeNode(*vals.front());
  std::queue<TreeNode*> q;
  q.push(root);

  size_t i{1};
  while (!q.empty() && i < vals.size()) {
    TreeNode* node = q.front();
    q.pop();

    if (i < vals.size() && vals[i].has_value()) {
      node->left = new TreeNode(*vals[i]);
      q.push(node->left);
    }
    ++i;

    if (i < vals.size() && vals[i].has_value()) {
      node->right = new TreeNode(*vals[i]);
      q.push(node->right);
    }
    ++i;
  }

  return root;
}

int main() {
  {
    // LeetCode example 1 -> deepest leaves 7 and 4 share the ancestor 2.
    TreeNode* root = build_tree({3, 5, 1, 6, 2, 0, 8, std::nullopt, std::nullopt, 7, 4});
    assert(lca_deepest_leaves(root)->val == 2);
  }
  {
    // LeetCode example 2 -> a single node is its own deepest leaf.
    TreeNode* root = build_tree({1});
    assert(lca_deepest_leaves(root)->val == 1);
  }
  {
    // LeetCode example 3.
    TreeNode* root = build_tree({0, 1, 3, std::nullopt, 2});
    assert(lca_deepest_leaves(root)->val == 2);
  }
  {
    // Only one side is deepest: the LCA is 3, not the root 1.
    // Tree: 1 -> left 2; 2 -> right 3.
    TreeNode* root = build_tree({1, 2, std::nullopt, std::nullopt, 3});
    assert(lca_deepest_leaves(root)->val == 3);
  }
  return 0;
}
