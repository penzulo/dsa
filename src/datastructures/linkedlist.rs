use std::ptr::NonNull;

/// A type alias for an optional, non-null pointer to a Node.
type NodePointer<T> = Option<NonNull<Node<T>>>;

/// The Node struct for a doubly linked list.
/// Each node contains a data element and pointers to the next and previous nodes.
struct Node<T> {
    next: NodePointer<T>,
    prev: NodePointer<T>,
    data: T,
}

/// The main LinkedList struct that holds the head and tail pointers.
/// It also keeps track of the number of elements in the list.
pub struct LinkedList<T> {
    head: NodePointer<T>,
    tail: NodePointer<T>,
    size: usize,
}

impl<T> Node<T> {
    /// Creates a new Node with the given data and no pointers.
    fn new(element: T) -> Self {
        Node {
            next: None,
            prev: None,
            data: element,
        }
    }
}

impl<T> LinkedList<T> {
    // Construction and Basic Information

    /// Creates and empty LinkedList.
    pub fn new() -> Self {
        LinkedList {
            head: None,
            tail: None,
            size: 0,
        }
    }

    /// Returns `true` if the list contains no elements.
    pub fn is_empty(&self) -> bool {
        self.head.is_none()
    }

    /// Returns the number of elements in the list.
    pub fn len(&self) -> usize {
        self.size
    }

    // Accessing the Elements
    // These methods provide references to elements without moving or removing them.

    /// Returns a reference to the front element of the list, or `None` if the list is empty.
    ///
    /// This method is `unsafe` because it works with raw pointers, which bypasses
    /// Rust's borrow checker. The safety of this method is guarenteed by the
    /// internal logic of the `LinkedList`
    ///
    /// # Time Complexity
    /// O(1)
    pub fn front(&self) -> Option<&T> {
        unsafe { self.head.as_ref().map(|node| &node.as_ref().data) }
    }

    /// Returns a mutable reference to the front element of the list, or `None` if the list is empty.
    ///
    /// # Time Complexity
    /// O(1)
    pub fn front_mut(&mut self) -> Option<&mut T> {
        unsafe { self.head.as_mut().map(|node| &mut node.as_mut().data) }
    }

    /// Returns a reference to the back element of the list, or `None` if the list is empty.
    ///
    /// # Time Complexity
    /// O(1)
    pub fn back(&self) -> Option<&T> {
        unsafe { self.tail.as_ref().map(|node| &node.as_ref().data) }
    }

    /// Returns a mutable reference to the back element of the list, or `None` if the list is empty.
    ///
    /// # Time Complexity
    /// O(1)
    pub fn back_mut(&mut self) -> Option<&mut T> {
        unsafe { self.tail.as_mut().map(|node| &mut node.as_mut().data) }
    }

    // NOTE: Modifying the Linked List
    // These are the core O(1) methods that make LinkedList useful.

    /// Adds a new element to the front of the list.
    ///
    /// # Time Complexity
    /// O(1)
    pub fn push_front(&mut self, element: T) {
        let node = Box::new(Node::new(element));
        let node_ptr = NonNull::from(Box::leak(node));

        unsafe {
            self.push_front_node(node_ptr);
        }
    }

    /// Adds a new element to the back of the list.
    ///
    /// # Time Complexity
    /// O(1)
    pub fn push_back(&mut self, element: T) {
        let node = Box::new(Node::new(element));
        let node_ptr = NonNull::from(Box::leak(node));

        unsafe {
            self.push_back_node(node_ptr);
        }
    }

    // Unsafe Helper Methods
    // These methods work with raw pointers and are wrapped in unsafe blocks for performance.
    unsafe fn push_front_node(&mut self, node: NonNull<Node<T>>) {
        unsafe {
            (*node.as_ptr()).next = self.head;
            (*node.as_ptr()).prev = None;
            let node = Some(node);

            match self.head {
                None => self.tail = node,
                Some(head) => (*head.as_ptr()).prev = node,
            }

            self.head = node;
            self.size += 1;
        }
    }

    unsafe fn push_back_node(&mut self, node: NonNull<Node<T>>) {
        unsafe {
            (*node.as_ptr()).next = None;
            (*node.as_ptr()).prev = self.tail;
            let node = Some(node);

            match self.tail {
                None => self.head = node,
                Some(tail) => (*tail.as_ptr()).next = node,
            }

            self.tail = node;
            self.size += 1;
        }
    }
}
