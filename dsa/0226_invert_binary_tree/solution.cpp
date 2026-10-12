// Problem: https://leetcode.com/problems/invert-binary-tree/

#include <cassert>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

using std::vector;

struct TreeNode {
  TreeNode* left{};
  TreeNode* right{};
  int val{};

  TreeNode() = default;
  explicit TreeNode(const int x) : val(x) {}
  TreeNode(TreeNode* l, const int x, TreeNode* r) : left(l), right(r), val(x) {}
};

auto invert_tree(TreeNode* root) -> TreeNode* {
  if (root == nullptr) {
    return root;
  }

  std::swap(root->left, root->right);
  invert_tree(root->left);
  invert_tree(root->right);

  return root;
}

auto to_level_order(TreeNode* root) -> vector<int> {
  if (root == nullptr) {
    return {};
  }

  vector<int> result;
  std::queue<TreeNode*> q;
  q.push(root);

  while (!q.empty()) {
    TreeNode* node = q.front();
    q.pop();
    result.push_back(node->val);
    if (node->left != nullptr) {
      q.push(node->left);
    }
    if (node->right != nullptr) {
      q.push(node->right);
    }
  }

  return result;
}

auto build_tree(const vector<std::optional<int>>& vals) -> TreeNode* {
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
    // Example 1: [4,2,7,1,3,6,9] -> [4,7,2,9,6,3,1].
    TreeNode* root = build_tree({4, 2, 7, 1, 3, 6, 9});
    const vector<int> expected{4, 7, 2, 9, 6, 3, 1};
    assert(to_level_order(invert_tree(root)) == expected);
  }
  {
    // Example 2: [2,1,3] -> [2,3,1].
    TreeNode* root = build_tree({2, 1, 3});
    const vector<int> expected{2, 3, 1};
    assert(to_level_order(invert_tree(root)) == expected);
  }
  {
    // Example 3: empty tree.
    TreeNode* root = build_tree({});
    const vector<int> expected{};
    assert(to_level_order(invert_tree(root)) == expected);
  }
  {
    // A single node tree is unchanged.
    TreeNode* root = build_tree({1});
    const vector<int> expected{1};
    assert(to_level_order(invert_tree(root)) == expected);
  }

  return 0;
}
