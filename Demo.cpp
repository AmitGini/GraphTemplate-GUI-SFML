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

    // Convert the tree to a min-heap and get a BFS iterator
    try {
        auto it = binaryTree.myHeap();
        std::cout << "\nMin-Heap (BFS):";
        for (; it != binaryTree.end_bfs(); ++it) {
            std::cout << " " << *it;
        }
        std::cout << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    // Display the tree and BFS traversal
    std::cout << "Binary Tree (BFS Traversal):" << std::endl;
    for (auto it = binaryTree.begin_bfs(); it != binaryTree.end_bfs(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
