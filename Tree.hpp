#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

namespace ariel {

    // Define the Tree class with default - Binary Tree (2 Children per Node)
    template <typename T, size_t K = 2>
    class Tree {
    public:
        
        // Define the Node struct
        struct Node {
            T key;
            Node* children[K];

            Node(const T& key) : key(key) {
                for (size_t i = 0; i < K; ++i) {
                    children[i] = nullptr;
                }
            }
        };

        Tree(); // Constructor
        ~Tree();  // Destructor

        void add_root(const T& key);  // Add root node
        void add_sub_node(Node* parent, const T& key);  // Add sub node
        void display() const;  // Display the tree
        Node* get_root() const;  // Get the root node

        // Iterator classes
        class BFSIterator;  // Breadth First Search Iterator
        class DFSIterator;  // Depth First Search Iterator
        class PreOrderIterator;  // PreOrder Iterator
        class InOrderIterator;  // InOrder Iterator
        class PostOrderIterator;  // PostOrder Iterator

        BFSIterator begin_bfs();  // Begin BFS Iterator
        BFSIterator end_bfs();  // End BFS Iterator
        DFSIterator begin_dfs();  // Begin DFS Iterator
        DFSIterator end_dfs();  // End DFS Iterator
        PreOrderIterator begin_preorder();  // Begin PreOrder Iterator
        PreOrderIterator end_preorder();  // End PreOrder Iterator
        InOrderIterator begin_inorder();  // Begin InOrder Iterator
        InOrderIterator end_inorder();  // End InOrder Iterator
        PostOrderIterator begin_postorder();  // Begin PostOrder Iterator
        PostOrderIterator end_postorder();  // End PostOrder Iterator
        
    private:
        Node* root;  // Root node - field

        // Helper functions to display the tree
        void displayHelper(Node* node, int indent) const;
        
        // Helper functions to clear the tree - delete every node in the Tree.
        void clear(Node* node);
    };

    // Define the BFSIterator class
    template <typename T, size_t K>
    class Tree<T, K>::BFSIterator {
    public:
        BFSIterator(Node* root);  // BFSIterator constructor

        // Overloaded operators
        bool operator!=(const BFSIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        BFSIterator& operator++();      // Increment operator

    private:
        std::queue<Node*> queue; // Queue to store the nodes
    };

    // Define the DFSIterator class
    template <typename T, size_t K>
    class Tree<T, K>::DFSIterator {
    public:
        DFSIterator(Node* root);  // DFSIterator constructor

        // Overloaded operators
        bool operator!=(const DFSIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        DFSIterator& operator++();  // Increment operator

    private:
        std::stack<Node*> stack;  // Stack to store the nodes
    };

    // Define the PreOrderIterator class
    template <typename T, size_t K>
    class Tree<T, K>::PreOrderIterator {
    public:
        PreOrderIterator(Node* root);  // PreOrderIterator constructor

        // Overloaded operators
        bool operator!=(const PreOrderIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        PreOrderIterator& operator++();  // Increment operator

    private:
        std::stack<Node*> stack;  // Stack to store the nodes
    };

    // Define the InOrderIterator class
    template <typename T, size_t K>
    class Tree<T, K>::InOrderIterator {
    public:
        InOrderIterator(Node* root);  // InOrderIterator constructor

        // Overloaded operators
        bool operator!=(const InOrderIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        InOrderIterator& operator++();  // Increment operator

    private:
        std::stack<Node*> stack;  // Stack to store the nodes
        void pushLeft(Node* node);  // Helper function to push the left nodes to the stack
    };

    // Define the PostOrderIterator class
    template <typename T, size_t K>
    class Tree<T, K>::PostOrderIterator {
    public:
        PostOrderIterator(Node* root);  // PostOrderIterator constructor

        // Overloaded operators
        bool operator!=(const PostOrderIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        PostOrderIterator& operator++();  // Increment operator

    private:
        std::stack<Node*> stack;  // Stack to store the nodes
        void pushLeft(Node* node);  // Helper function to push the left nodes to the stack

    };

} // namespace ariel

#include "Tree.cpp"
#endif 
