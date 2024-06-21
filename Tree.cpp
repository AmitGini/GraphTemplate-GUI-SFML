#ifndef TREE_CPP
#define TREE_CPP

#include "Tree.hpp"
#include <queue>
#include <stack>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

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
    void Tree<T, K>::draw(sf::RenderWindow &window) const
    {
        if (root) {
            float initialDistance = window.getSize().y / 3;  // Initial distance from root to first level of children
            drawNode(window, root, sf::Vector2f(window.getSize().x / 2, 50), 90, initialDistance, 0);
        }
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
    void Tree<T, K>::drawNode(sf::RenderWindow& window, Node* node, sf::Vector2f position, float angle, float distance, int depth) const
    {
        if (!node) return;

        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(position.x - circle.getRadius(), position.y - circle.getRadius());
        window.draw(circle);

        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font\n";
        }
        sf::Text text;
        text.setFont(font);

        // Use std::ostringstream to convert the node's key to a string
        std::ostringstream oss;
        oss << node->key;
        text.setString(oss.str());

        // Set the text properties
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(position.x - circle.getRadius() / 2, position.y - circle.getRadius() / 2);
        window.draw(text);

        float new_distance = distance / 1.5f;  // Reduce distance for next level
        float angleIncrement = 45.0f / (K - 1);  // Distribute angles for child nodes

        // Draw all the nodes with the following order: Recursive (Parent Node -> Arrow to Child Node -> Child Node)
        for (size_t i = 0; i < K; ++i) {
            if (node->children[i]) {
                float childAngle = angle + (i - (K / 2.0f)) * angleIncrement;
                float rad = childAngle * 3.14159265359 / 180.0f;
                sf::Vector2f new_position = position + sf::Vector2f(cos(rad) * distance, sin(rad) * distance);

                // Draw the child node
                drawNode(window, node->children[i], new_position, childAngle, new_distance, depth + 1);
                drawArrow(window, position, new_position);  // Draw the arrow

            }
        }
    }

    template <typename T, size_t K>
    void Tree<T, K>::drawArrow(sf::RenderWindow &window, sf::Vector2f start, sf::Vector2f end) const
    {
        // Draw the main line
        sf::Vertex line[] = {
            sf::Vertex(start),
            sf::Vertex(end)
        };
        window.draw(line, 2, sf::Lines);

        // Calculate the direction of the arrow
        sf::Vector2f direction = end - start;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        // Set the size of the arrowhead
        float arrowSize = 10.0f;
        
        // Calculate the points of the arrowhead
        sf::Vector2f arrowPoint1 = end - direction * arrowSize + sf::Vector2f(-direction.y, direction.x) * arrowSize * 0.5f;
        sf::Vector2f arrowPoint2 = end - direction * arrowSize + sf::Vector2f(direction.y, -direction.x) * arrowSize * 0.5f;

        sf::Vertex arrowhead[] = {
            sf::Vertex(end),
            sf::Vertex(arrowPoint1),
            sf::Vertex(end),
            sf::Vertex(arrowPoint2)
        };
        window.draw(arrowhead, 4, sf::Lines);
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

    template <typename T, size_t K>
    typename Tree<T, K>::BFSIterator Tree<T, K>::myHeap()
    {
        if (K != 2) {
            throw std::invalid_argument("Tree is not binary");
        }

        // Convert the binary tree to a vector
        std::vector<T> elements;
        std::queue<Node*> nodeQueue;
        if (root) {
            nodeQueue.push(root);
        }
        while (!nodeQueue.empty()) {
            Node* current = nodeQueue.front();
            nodeQueue.pop();
            elements.push_back(current->key);
            for (size_t i = 0; i < K; ++i) {
                if (current->children[i]) {
                    nodeQueue.push(current->children[i]);
                }
            }
        }

        // Build a min heap from the elements
        std::make_heap(elements.begin(), elements.end(), std::greater<T>());

        // Rebuild the tree as a min heap
        std::queue<Node**> pointerQueue;
        pointerQueue.push(&root);
        for (const T& element : elements) {
            Node** currentPointer = pointerQueue.front();
            pointerQueue.pop();
            *currentPointer = new Node(element);
            pointerQueue.push(&((*currentPointer)->children[0]));
            pointerQueue.push(&((*currentPointer)->children[1]));
        }

        return this->begin_bfs();  // Return BFS iterator to the minimum heap
    }

    // BFSIterator implementation
    template <typename T, size_t K>
    Tree<T, K>::BFSIterator::BFSIterator(Node* root) {
        if (root) {
            queue.push(root);
        }
    }

    //TODO - Edit 
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

    //TODO - Edit 
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

    //TODO - Edit 
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

    //TODO - Edit 
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

    // TODO - Edit 
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