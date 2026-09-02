# Core Idea
- **Simultaneous Traversal**: We iterate through both linked lists at the same time. Because the lists store digits in reverse order (least significant digit first), we can calculate the carry-over naturally, exactly like grade-school addition.
- **Null-Safety & Unequal Lengths**: We use pointers because lists can be different lengths. If one pointer hits `nullptr` early, we simply substitute its value with 0 (e.g., `a = l1 ? l1->data : 0`), allowing the loop to process the remaining digits of the longer list.
- **Dummy Head Pattern**: We initialize a stack-allocated dummy node to anchor the start of our result list. A current pointer builds the list without losing track of the head.
- **The Math**: For each iteration, `sum = a + b + carry`. The new node's value is `sum % 10`, and the carry updates to `sum / 10`.
- **Return Value**: We return `dummy.next` to cleanly skip our initial placeholder node.

## Resource Stats
|Resource|Complexity|Justification|
|-----|------|-----|
|Time|	O(max(m, n))|	We traverse the longest list exactly once.|
|Space|	O(max(m, n))|	The output list requires allocating a new node for every digit (plus at most 1 extra node for a final carry).|
