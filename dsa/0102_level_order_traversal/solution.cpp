// Problem: https://leetcode.com/problems/binary-tree-level-order-traversal/

#include <cassert>
#include <optional>
#include <queue>
#include <ranges>
#include <vector>

using std::vector;
using result_t = vector<vector<int>>;

struct TreeNode {
  TreeNode* left{};
  TreeNode* right{};
  int val{};

  TreeNode() = default;
  explicit TreeNode(const int x) : val(x) {}
  TreeNode(TreeNode* l, const int x, TreeNode* r) : left(l), right(r), val(x) {}
};

auto level_order(TreeNode* root) -> result_t {
  result_t result;
  std::queue<TreeNode*> q;
  q.push(root);

  while (!q.empty()) {
    vector<int> level;
    // Snapshot the width of the current level; q's size grows as we enqueue
    // children, so reading it inline would merge this level with the next.
    const auto level_size = q.size();
    for (size_t i{}; i < level_size; ++i) {
      auto* node = q.front();
      q.pop();
      if (node != nullptr) {
        level.emplace_back(node->val);
        q.push(node->left);
        q.push(node->right);
      }
    }

    if (!level.empty()) {
      result.push_back(level);
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
    // Example 1: [3,9,20,null,null,15,7].
    TreeNode* root = build_tree({3, 9, 20, std::nullopt, std::nullopt, 15, 7});
    const result_t expected = {{3}, {9, 20}, {15, 7}};
    assert(level_order(root) == expected);
  }
  {
    // A single-node tree.
    TreeNode* root = build_tree({1});
    const result_t expected = {{1}};
    assert(level_order(root) == expected);
  }
  {
    // An empty tree yields no levels.
    TreeNode* root = build_tree({});
    const result_t expected = {};
    assert(level_order(root) == expected);
  }
  {
    // A two-level tree.
    TreeNode* root = build_tree({1, 2, 3});
    const result_t expected = {{1}, {2, 3}};
    assert(level_order(root) == expected);
  }

  return 0;
}
