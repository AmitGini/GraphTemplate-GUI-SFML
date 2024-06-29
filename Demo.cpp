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


    // Display the tree and BFS traversal
    std::cout << "Binary Tree (BFS Traversal):" << std::endl;
    for (auto it = binaryTree.begin_bfs(); it != binaryTree.end_bfs(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout<<"\n" << std::endl;

    std::cout<< "Binary Tree (DFS Traversal):" << std::endl;
    for (auto it = binaryTree.begin_dfs(); it != binaryTree.end_dfs(); ++it) {
        std::cout<< *it << std::endl;
    }
    std::cout<<"\n" << std::endl;

    std::cout << "Pre-Order Traversal:" << std::endl;
    for (auto it = binaryTree.begin_pre_order(); it != binaryTree.end_pre_order(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout<<"\n" << std::endl;

    std::cout<< "In-Order Traversal:" << std::endl;
    for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout<<"\n" << std::endl;

    std::cout<< "Post-Order Traversal:" << std::endl;
    for (auto it = binaryTree.begin_post_order(); it != binaryTree.end_post_order(); ++it) {
        std::cout << *it << std::endl;
    }

    try {
        auto it = binaryTree.myHeap();
        std::cout << "\nMin-Heap (BFS):" << std::endl;
        int level = 0;
        int num_nodes = 1;
        int printed_nodes = 0;
        while (it != binaryTree.end_bfs()) {
            if (printed_nodes == num_nodes) {
                std::cout << std::endl;
                level++;
                num_nodes *= 2;
                printed_nodes = 0;
            }
            std::cout << *it << " ";
            ++it;
            printed_nodes++;
        }
        std::cout << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    Tree<int, 3> tree;
    tree.add_root(1);
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    tree.add_sub_node(tree.get_root(), 4);
    tree.add_sub_node(tree.get_root()->children[0], 5);
    tree.add_sub_node(tree.get_root()->children[1], 6);
    tree.add_sub_node(tree.get_root()->children[1], 7);
    tree.add_sub_node(tree.get_root()->children[2], 8);
    tree.add_sub_node(tree.get_root()->children[2], 9);
    tree.add_sub_node(tree.get_root()->children[2], 10);
    
    std::cout<<"Tree K=3 DFS:"<< std::endl;
    for(auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // All printing should be in the same order as the DFS iterator
    std::cout <<"Tree K=3 In-Order:"<< std::endl;
    for(auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout<<"Tree K=3 Pre-Order:"<< std::endl;
    for(auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout<<"Tree K=3 Post-Order:"<< std::endl;
    for(auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Create a window to draw the tree
    sf::RenderWindow window(sf::VideoMode(800, 600), "Complex Binary-Tree Drawing");

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

    sf::RenderWindow window2(sf::VideoMode(800, 600), "Tree <int, 3> Drawing");
    while (window2.isOpen()) {
        sf::Event event;
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window2.close();
            }
        }

        window2.clear(sf::Color::Black);
        tree.draw(window2);
        window2.display();
    }

    return 0;
}
