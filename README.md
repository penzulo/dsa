# 🦀 dsa 🦀

This repository is a comprehensive collection of Data Structures and Algorithms (DSA) implemented in **Rust**. The project is structured as a library to enable modularity and easy testing, with the `main.rs` file serving as a client to demonstrate the functionality.

The primary goal of this project is to provide a practical learning environment for mastering core DSA concepts while leveraging Rust's powerful features like memory safety, generics, and a robust type system.

## 📁 Project Structure

The project follows a clean, organized structure to separate implementation from documentation and testing.

-   **`src/`**: Contains the Rust source code for the library.
    -   **`algorithms/`**: Implementations of various searching and sorting algorithms.
    -   **`data_structures/`**: Custom implementations of fundamental data structures.
-   **`notes/`**: A dedicated folder for detailed Markdown notes on each algorithm's logic, complexity, and implementation details. This is an excellent resource for a deeper understanding.
-   **`main.rs`**: A client file used to call and test the algorithms from the library.
-   **`Cargo.toml`**: The project manifest for managing dependencies and project metadata.

## ⚙️ Algorithms and Data Structures Implemented

### Sorting Algorithms
-   **Bubble Sort**: A simple, comparison-based sorting algorithm with an optimized early exit.
-   **Selection Sort**: An in-place comparison sort that is simple to implement but less efficient on large lists.
-   **Insertion Sort**: Efficient for small data sets and nearly sorted arrays.
-   **Merge Sort**: A reliable $O(n \log n)$ "divide and conquer" algorithm.
-   **Quick Sort**: An in-place "divide and conquer" algorithm, highly efficient on average.

### Searching Algorithms
-   **Linear Search**: A fundamental search algorithm for unsorted data.
-   **Binary Search**: An efficient search algorithm for sorted data.

## 🚀 Getting Started

To run the `main.rs` examples or your own tests, you will need the Rust toolchain installed.

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/penzulo/dsa.git](https://github.com/penzulo/dsa.git)
    cd dsa
    ```

2.  **Run the main program:**
    ```bash
    cargo run
    ```

3.  **Run the unit tests:**
    ```bash
    cargo test
    ```

## 📝 Learning and Notes

Each algorithm in this repository is accompanied by detailed notes in the `notes/` directory. These Markdown files contain:
-   A high-level description of the algorithm's logic.
-   Analysis of its time and space complexity.
-   Key implementation details and trade-offs in Rust.

Feel free to add your own notes, diagrams, or improvements as you work through the exercises.

## 🤝 Contributing

This project is a personal learning tool, but feel free to fork the repository and use it for your own DSA practice!
