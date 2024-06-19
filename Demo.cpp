#include "Tree.hpp"
#include <string>
#include <iostream>

using namespace ariel;

int main() {
    Tree<int> binaryTree;
    binaryTree.add_root(1);

    auto root = binaryTree.get_root();
    binaryTree.add_sub_node(root, 2);
    binaryTree.add_sub_node(root, 3);

    auto child1 = root->children[0];
    binaryTree.add_sub_node(child1, 4);
    binaryTree.add_sub_node(child1, 5);

    std::cout << "Binary Tree:" << std::endl;
    binaryTree.display();

    // Corrected usage of BFS iterator
    std::cout << "\nBFS Traversal:" << std::endl;
    for (auto it = binaryTree.begin_bfs(); it != binaryTree.end_bfs(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Corrected usage of DFS iterator
    std::cout << "\nDFS Traversal:" << std::endl;
    for (auto it = binaryTree.begin_dfs(); it != binaryTree.end_dfs(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    Tree<std::string, 3> ternaryTree;
    ternaryTree.add_root("root");

    auto ternaryRoot = ternaryTree.get_root();
    ternaryTree.add_sub_node(ternaryRoot, "child1");
    ternaryTree.add_sub_node(ternaryRoot, "child2");
    ternaryTree.add_sub_node(ternaryRoot, "child3");

    auto ternaryChild1 = ternaryRoot->children[0];
    ternaryTree.add_sub_node(ternaryChild1, "child4");

    std::cout << "\nTernary Tree:" << std::endl;
    ternaryTree.display();

    // Corrected usage of PreOrder iterator
    std::cout << "\nPreOrder Traversal:" << std::endl;
    for (auto it = ternaryTree.begin_preorder(); it != ternaryTree.end_preorder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "\nPostOrder Traversal:" << std::endl;
    for (auto it = ternaryTree.begin_postorder(); it != ternaryTree.end_postorder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout<< "\nInOrder Traversal:" << std::endl;
    for (auto it = ternaryTree.begin_inorder(); it != ternaryTree.end_inorder(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}
