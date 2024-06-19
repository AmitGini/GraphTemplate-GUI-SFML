#ifndef TREE_CPP
#define TREE_CPP

#include "Tree.hpp"
#include <queue>
#include <stack>

namespace ariel {

    template <typename T, size_t K>
    Tree<T, K>::Tree() : root(nullptr) {}

    template <typename T, size_t K>
    Tree<T, K>::~Tree() {
        clear(root);
    }

    template <typename T, size_t K>
    void Tree<T, K>::add_root(const T& key) {
        if (!root) {
            root = new Node(key);
        } else {
            root->key = key;
        }
    }

    template <typename T, size_t K>
    void Tree<T, K>::add_sub_node(Node* parent, const T& key) {
        if (!parent) return;

        for (size_t i = 0; i < K; ++i) {
            if (!parent->children[i]) {
                parent->children[i] = new Node(key);
                return;
            }
        }
        std::cerr << "No empty slot to add sub node." << std::endl;
    }

    template <typename T, size_t K>
    void Tree<T, K>::display() const {
        displayHelper(root, 0);
    }

    template <typename T, size_t K>
    typename Tree<T, K>::Node* Tree<T, K>::get_root() const {
        return root;
    }

    template <typename T, size_t K>
    void Tree<T, K>::displayHelper(Node* node, int indent) const {
        if (!node) return;
        for (int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << node->key << std::endl;
        for (size_t i = 0; i < K; ++i) {
            displayHelper(node->children[i], indent + 1);
        }
    }

    template <typename T, size_t K>
    void Tree<T, K>::clear(Node* node) {
        if (!node) return;
        for (size_t i = 0; i < K; ++i) {
            clear(node->children[i]);
        }
        delete node;
    }

    template <typename T, size_t K>
    typename Tree<T, K>::BFSIterator Tree<T, K>::begin_bfs() {
        return BFSIterator(root);
    }

    template <typename T, size_t K>
    typename Tree<T, K>::BFSIterator Tree<T, K>::end_bfs() {
        return BFSIterator(nullptr);
    }

    template <typename T, size_t K>
    typename Tree<T, K>::DFSIterator Tree<T, K>::begin_dfs() {
        return DFSIterator(root);
    }

    template <typename T, size_t K>
    typename Tree<T, K>::DFSIterator Tree<T, K>::end_dfs() {
        return DFSIterator(nullptr);
    }

    template <typename T, size_t K>
    typename Tree<T, K>::PreOrderIterator Tree<T, K>::begin_preorder() {
        return PreOrderIterator(root);
    }

    template <typename T, size_t K>
    typename Tree<T, K>::PreOrderIterator Tree<T, K>::end_preorder() {
        return PreOrderIterator(nullptr);
    }

    template <typename T, size_t K>
    typename Tree<T, K>::InOrderIterator Tree<T, K>::begin_inorder() {
        return InOrderIterator(root);
    }

    template <typename T, size_t K>
    typename Tree<T, K>::InOrderIterator Tree<T, K>::end_inorder() {
        return InOrderIterator(nullptr);
    }

    template <typename T, size_t K>
    typename Tree<T, K>::PostOrderIterator Tree<T, K>::begin_postorder() {
        return PostOrderIterator(root);
    }

    template <typename T, size_t K>
    typename Tree<T, K>::PostOrderIterator Tree<T, K>::end_postorder() {
        return PostOrderIterator(nullptr);
    }

    // BFSIterator implementation
    template <typename T, size_t K>
    Tree<T, K>::BFSIterator::BFSIterator(Node* root) {
        if (root) {
            queue.push(root);
        }
    }

    template <typename T, size_t K>
    bool Tree<T, K>::BFSIterator::operator!=(const BFSIterator& other) const {
        return !queue.empty();
    }

    template <typename T, size_t K>
    const T& Tree<T, K>::BFSIterator::operator*() const {
        return queue.front()->key;
    }

    template <typename T, size_t K>
    typename Tree<T, K>::BFSIterator& Tree<T, K>::BFSIterator::operator++() {
        Node* current = queue.front();
        queue.pop();
        for (size_t i = 0; i < K; ++i) {
            if (current->children[i]) {
                queue.push(current->children[i]);
            }
        }
        return *this;
    }

    // DFSIterator implementation
    template <typename T, size_t K>
    Tree<T, K>::DFSIterator::DFSIterator(Node* root) {
        if (root) {
            stack.push(root);
        }
    }

    template <typename T, size_t K>
    bool Tree<T, K>::DFSIterator::operator!=(const DFSIterator& other) const {
        return !stack.empty();
    }

    template <typename T, size_t K>
    const T& Tree<T, K>::DFSIterator::operator*() const {
        return stack.top()->key;
    }

    template <typename T, size_t K>
    typename Tree<T, K>::DFSIterator& Tree<T, K>::DFSIterator::operator++() {
        Node* current = stack.top();
        stack.pop();
        for (size_t i = K; i-- > 0;) {
            if (current->children[i]) {
                stack.push(current->children[i]);
            }
        }
        return *this;
    }

    // PreOrderIterator implementation
    template <typename T, size_t K>
    Tree<T, K>::PreOrderIterator::PreOrderIterator(Node* root) {
        if (root) {
            stack.push(root);
        }
    }

    template <typename T, size_t K>
    bool Tree<T, K>::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
        return !stack.empty();
    }

    template <typename T, size_t K>
    const T& Tree<T, K>::PreOrderIterator::operator*() const {
        return stack.top()->key;
    }

    template <typename T, size_t K>
    typename Tree<T, K>::PreOrderIterator& Tree<T, K>::PreOrderIterator::operator++() {
        Node* current = stack.top();
        stack.pop();
        for (size_t i = K; i-- > 0;) {
            if (current->children[i]) {
                stack.push(current->children[i]);
            }
        }
        return *this;
    }

    // InOrderIterator implementation
    template <typename T, size_t K>
    Tree<T, K>::InOrderIterator::InOrderIterator(Node* root) {
        pushLeft(root);
    }

    template <typename T, size_t K>
    bool Tree<T, K>::InOrderIterator::operator!=(const InOrderIterator& other) const {
        return !stack.empty();
    }

    template <typename T, size_t K>
    const T& Tree<T, K>::InOrderIterator::operator*() const {
        return stack.top()->key;
    }

    template <typename T, size_t K>
    typename Tree<T, K>::InOrderIterator& Tree<T, K>::InOrderIterator::operator++() {
        Node* current = stack.top();
        stack.pop();
        pushLeft(current->children[1]); // Assuming binary tree for InOrder
        return *this;
    }

    template <typename T, size_t K>
    void Tree<T, K>::InOrderIterator::pushLeft(Node* node) {
        while (node) {
            stack.push(node);
            node = node->children[0]; // Assuming binary tree for InOrder
        }
    }

    // PostOrderIterator implementation
    template <typename T, size_t K>
    Tree<T, K>::PostOrderIterator::PostOrderIterator(Node* root) {
        pushLeft(root);
    }

    template <typename T, size_t K>
    bool Tree<T, K>::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
        return !stack.empty();
    }

    template <typename T, size_t K>
    const T& Tree<T, K>::PostOrderIterator::operator*() const {
        return stack.top()->key;
    }

    template <typename T, size_t K>
    typename Tree<T, K>::PostOrderIterator& Tree<T, K>::PostOrderIterator::operator++() {
        Node* current = stack.top();
        stack.pop();
        if (!stack.empty() && stack.top()->children[1] == current) { // Assuming binary tree for PostOrder
            pushLeft(stack.top()->children[1]);
        }
        return *this;
    }

    template <typename T, size_t K>
    void Tree<T, K>::PostOrderIterator::pushLeft(Node* node) {
        while (node) {
            if (node->children[1]) { // Assuming binary tree for PostOrder
                stack.push(node->children[1]);
            }
            stack.push(node);
            node = node->children[0]; // Assuming binary tree for PostOrder
        }
    }
}

#endif 