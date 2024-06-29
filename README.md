# Tree Data Structure & Demo With Complex Numbers & GUI-SFML

This repository contains a C++ implementation of a general tree data structure and operations on complex numbers. The tree supports various traversal methods and can visualize the tree structure using SFML. The complex number class provides basic arithmetic operations and comparison operators.

## Features

### Tree Data Structure
- Supports any number of children per node (default is binary tree with 2 children).
- Various traversal methods: BFS, DFS, PreOrder, InOrder, PostOrder.
- Visualization of the tree using SFML.
- Can transform the tree into a min-heap.

### Complex Number Class
- Basic arithmetic operations: addition, subtraction, multiplication.
- Comparison operators: equality, inequality, less than, greater than.
- Stream input and output operators.

## Dependencies

- SFML library for graphical visualization of the tree.
- C++ standard libraries: `<iostream>`, `<vector>`, `<queue>`, `<stack>`, `<cmath>`, `<functional>`, `<sstream>`, `<unordered_set>`.

## Usage

### Example - Tree Template & Complex & GUI-SFML

```cpp
#include "Tree.hpp"
#include "Complex.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace ariel;

int main() {
    // Create a binary tree of Complex numbers
    Tree<Complex> binaryTree;
    binaryTree.add_root(Complex(1, 1));

    auto root = binaryTree.get_root();
    binaryTree.add_sub_node(root, Complex(2, 2));
    binaryTree.add_sub_node(root, Complex(3, 3));

    auto child1 = root->children[0];
    binaryTree.add_sub_node(child1, Complex(4, 4));
    binaryTree.add_sub_node(child1, Complex(5, 5));

    auto child2 = root->children[1];
    binaryTree.add_sub_node(child2, Complex(6, 6));
    binaryTree.add_sub_node(child2, Complex(7, 7));

    // Convert the tree to a min-heap and get a BFS iterator
    try {
        auto it = binaryTree.myHeap();
        std::cout << "\nMin-Heap (BFS):";
        for (; it != binaryTree.end_bfs(); ++it) {
            std::cout << " " << *it;
        }
        std::cout << "\n" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    // Display the tree and BFS traversal
    std::cout << "Binary Tree (BFS Traversal):" << std::endl;
    for (auto it = binaryTree.begin_bfs(); it != binaryTree.end_bfs(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "\n" << std::endl;

    // Display other traversal methods similarly...

    // Create a window to draw the tree
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Tree Drawing");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        binaryTree.draw(window);
        window.display();
    }

    return 0;
}
