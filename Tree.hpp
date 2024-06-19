#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

namespace ariel {

    template <typename T, size_t K = 2>
    class Tree {
    public:
        struct Node {
            T key;
            Node* children[K];

            Node(const T& key) : key(key) {
                for (size_t i = 0; i < K; ++i) {
                    children[i] = nullptr;
                }
            }
        };

        Tree();
        ~Tree();

        void add_root(const T& key);
        void add_sub_node(Node* parent, const T& key);
        void display() const;
        Node* get_root() const;

        // Iterator classes
        class BFSIterator;
        class DFSIterator;
        class PreOrderIterator;
        class InOrderIterator;
        class PostOrderIterator;

        BFSIterator begin_bfs();
        BFSIterator end_bfs();
        DFSIterator begin_dfs();
        DFSIterator end_dfs();
        PreOrderIterator begin_preorder();
        PreOrderIterator end_preorder();
        InOrderIterator begin_inorder();
        InOrderIterator end_inorder();
        PostOrderIterator begin_postorder();
        PostOrderIterator end_postorder();
        
    private:
        Node* root;

        void displayHelper(Node* node, int indent) const;
        void clear(Node* node);
    };

    template <typename T, size_t K>
    class Tree<T, K>::BFSIterator {
    public:
        BFSIterator(Node* root);

        bool operator!=(const BFSIterator& other) const;
        const T& operator*() const;
        BFSIterator& operator++();

    private:
        std::queue<Node*> queue;
    };

    template <typename T, size_t K>
    class Tree<T, K>::DFSIterator {
    public:
        DFSIterator(Node* root);

        bool operator!=(const DFSIterator& other) const;
        const T& operator*() const;
        DFSIterator& operator++();

    private:
        std::stack<Node*> stack;
    };

    template <typename T, size_t K>
    class Tree<T, K>::PreOrderIterator {
    public:
        PreOrderIterator(Node* root);

        bool operator!=(const PreOrderIterator& other) const;
        const T& operator*() const;
        PreOrderIterator& operator++();

    private:
        std::stack<Node*> stack;
    };

    template <typename T, size_t K>
    class Tree<T, K>::InOrderIterator {
    public:
        InOrderIterator(Node* root);

        bool operator!=(const InOrderIterator& other) const;
        const T& operator*() const;
        InOrderIterator& operator++();

    private:
        void pushLeft(Node* node);
        std::stack<Node*> stack;
    };

    template <typename T, size_t K>
    class Tree<T, K>::PostOrderIterator {
    public:
        PostOrderIterator(Node* root);

        bool operator!=(const PostOrderIterator& other) const;
        const T& operator*() const;
        PostOrderIterator& operator++();

    private:
        void pushLeft(Node* node);
        std::stack<Node*> stack;
    };

} // namespace ariel

#include "Tree.cpp"
#endif 
