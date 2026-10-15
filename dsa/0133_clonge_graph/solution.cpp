// Problem: https://leetcode.com/problems/clone-graph/
#include <cassert>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::vector, std::unordered_map, std::unordered_set, std::queue;

struct Node {
  int val{};
  vector<Node*> neighbours;

  explicit Node(const int _val) : val(_val) {}
};

auto clone_graph(Node* source) -> Node* {
  // Check if the source is null
  if (source == nullptr) {
    return source;
  }

  unordered_map<Node*, Node*> cloned;  // K: Original Node, Cloned Node
  queue<Node*> q;                      // only contains original nodes

  cloned.emplace(source, new Node(source->val));
  q.push(source);

  while (!q.empty()) {
    // get front element
    auto* original = q.front();
    q.pop();

    auto* copy = cloned.at(original);

    for (auto* neighbour : original->neighbours) {
      if (!cloned.contains(neighbour)) {
        cloned.emplace(neighbour, new Node(neighbour->val));
        q.push(neighbour);
      }

      copy->neighbours.push_back(cloned.at(neighbour));
    }
  }

  return cloned.at(source);
}

// Every node reachable from `start`, in BFS order.
auto all_nodes(const Node* start) -> vector<const Node*> {
  vector<const Node*> out;
  if (start == nullptr) {
    return out;
  }
  unordered_set<const Node*> seen;
  queue<const Node*> q;
  seen.insert(start);
  q.push(start);
  while (!q.empty()) {
    const Node* node = q.front();
    q.pop();
    out.push_back(node);
    for (const Node* next : node->neighbours) {
      if (seen.insert(next).second) {
        q.push(next);
      }
    }
  }
  return out;
}

// True when `a` and `b` have the same values and the same adjacency structure.
auto same_graph(const Node* a, const Node* b) -> bool {
  if (a == nullptr || b == nullptr) {
    return a == b;
  }
  unordered_map<const Node*, const Node*> seen;
  seen.emplace(a, b);
  queue<const Node*> q;
  q.push(a);

  while (!q.empty()) {
    const Node* node_a = q.front();
    q.pop();
    const Node* node_b = seen.at(node_a);

    if (node_a->val != node_b->val || node_a->neighbours.size() != node_b->neighbours.size()) {
      return false;
    }

    for (size_t i{}; i < node_a->neighbours.size(); ++i) {
      const Node* next_a = node_a->neighbours.at(i);
      const Node* next_b = node_b->neighbours.at(i);

      const auto [it, inserted] = seen.emplace(next_a, next_b);
      if (inserted) {
        q.push(next_a);
      } else if (it->second != next_b) {
        return false;  // same original reached via a different clone
      }
    }
  }
  return true;
}

int main() {
  // An empty graph clones to nullptr.
  assert(clone_graph(nullptr) == nullptr);

  {
    // Single node without neighbours.
    Node a{1};
    Node* copy = clone_graph(&a);
    assert(copy != nullptr);
    assert(copy != &a);
    assert(copy->val == 1);
    assert(copy->neighbours.empty());
  }

  {
    // Two nodes joined by a single bidirectional edge.
    Node a{1};
    Node b{2};
    a.neighbours.push_back(&b);
    b.neighbours.push_back(&a);

    Node* copy = clone_graph(&a);
    assert(copy != &a);
    assert(same_graph(&a, copy));
    assert(copy->neighbours.at(0) != &b);  // must be a fresh node
  }

  {
    // LeetCode example: adjacency list [[2,4],[1,3],[2,4],[1,3]] -- a 4-cycle.
    Node n1{1};
    Node n2{2};
    Node n3{3};
    Node n4{4};
    n1.neighbours = {&n2, &n4};
    n2.neighbours = {&n1, &n3};
    n3.neighbours = {&n2, &n4};
    n4.neighbours = {&n3, &n1};

    Node* copy = clone_graph(&n1);
    assert(copy != &n1);
    assert(same_graph(&n1, copy));

    // The clone must be a disjoint set of nodes, never aliases of the originals.
    const vector<const Node*> originals = all_nodes(&n1);
    const unordered_set<const Node*> original_set{originals.begin(), originals.end()};
    for (const Node* node : all_nodes(copy)) {
      assert(!original_set.contains(node));
    }
  }

  return 0;
}
