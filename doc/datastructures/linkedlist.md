# Doubly Linked List

## Overview

This Rust implementation defines a **doubly linked list** data structure using **raw pointers** (`NonNull`) to achieve efficient O(1) insertions at both ends of the list. Managing linked list nodes with raw pointers requires `unsafe` code, but the API presented is mostly safe, encapsulating unsafe blocks internally.

---

### Key Structures
- **Node<T>**: Holds `data: T`, and pointers `next` & `prev` as `Option<NonNull<Node<T>>>`.
- **LinkedList<T>**: Tracks `head`, `tail` pointers and `size`.

### Type Alias
```
type NodePointer<T> = Option<NonNull<Node<T>>>;
```

---

### Basic Methods

- `new()`: Creates an empty list.
- `is_empty()`: Checks if the list is empty.
- `len()`: Returns number of elements.
- `front() / back()`: Returns references to first/last elements (unsafe internally).
- `front_mut() / back_mut()`: Mutable references to first/last elements.

---

### Adding Elements (O(1))

- **push_front(element)**:
  - Allocates a new node on heap.
  - Uses `Box::leak` and `NonNull` pointer.
  - Calls unsafe helper `push_front_node` to insert at head.

- **push_back(element)**:
  - Similar to `push_front`, inserts at tail with `push_back_node`.

---

### Safety Notes

- Raw pointers (`NonNull`) bypass Rust’s borrow checker.
- Unsafe code is isolated within the implementation.
- Nodes are heap allocated and leaked to keep pointers valid.
- No automatic cleanup yet (`Drop` is not implemented).
- Safe public API hides unsafe internals.

---

### Performance Summary

| Operation           | Time Complexity |
|---------------------|-----------------|
| push_front, push_back| O(1)            |
| front, back          | O(1)            |
| len, is_empty        | O(1)            |

---

### Summary

- Efficient doubly linked list using unsafe raw pointers.
- Manual pointer management needed.
- Suitable for learning unsafe Rust and linked list internals.
- Completeness requires adding removal, iteration, and `Drop`.
