// Problem: https://leetcode.com/problems/max-depth-of-binary-tree/

#include <cassert>
#include <queue>
#include <vector>

struct TreeNode {
  TreeNode* left{};
  TreeNode* right{};
  int val{};

  TreeNode() = default;
  explicit TreeNode(const int x) : val(x) {}
  TreeNode(TreeNode* l, const int x, TreeNode* r) : left(l), right(r), val(x) {}
};

auto max_depth(const TreeNode* root) -> int {
  if (root == nullptr) {
    return 0;
  }

  auto max_left = max_depth(root->left);
  auto max_right = max_depth(root->right);
  return 1 + std::max(max_left, max_right);
}

using std::vector;

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
    // Example 1: [3,9,20,null,null,15,7].
    TreeNode* root = build_tree({3, 9, 20, std::nullopt, std::nullopt, 15, 7});
    assert(max_depth(root) == 3);
  }
  {
    // Example 2: [1,null,2].
    TreeNode* root = build_tree({1, std::nullopt, 2});
    assert(max_depth(root) == 2);
  }
  {
    // Empty tree.
    TreeNode* root = build_tree({});
    assert(max_depth(root) == 0);
  }
  {
    // A full tree of depth three.
    TreeNode* root = build_tree({1, 2, 3, 4, 5});
    assert(max_depth(root) == 3);
  }

  return 0;
}
