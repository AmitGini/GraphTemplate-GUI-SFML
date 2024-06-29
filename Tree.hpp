#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <sstream>
#include <unordered_set>

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

        // Draw the tree 
        void draw(sf::RenderWindow& window) const;

        // Iterator classes
        class BFSIterator;  // Breadth First Search Iterator
        class DFSIterator;  // Depth First Search Iterator
        class PreOrderIterator;  // PreOrder Iterator
        class InOrderIterator;  // InOrder Iterator
        class PostOrderIterator;  // PostOrder Iterator

        // Member Function Declarations of the 'Tree' class template
        BFSIterator begin_bfs();  // Begin BFS Iterator
        BFSIterator end_bfs();  // End BFS Iterator
        DFSIterator begin_dfs();  // Begin DFS Iterator
        DFSIterator end_dfs();  // End DFS Iterator
        PreOrderIterator begin_pre_order();  // Begin PreOrder Iterator
        PreOrderIterator end_pre_order();  // End PreOrder Iterator
        InOrderIterator begin_in_order();  // Begin InOrder Iterator
        InOrderIterator end_in_order();  // End InOrder Iterator
        PostOrderIterator begin_post_order();  // Begin PostOrder Iterator
        PostOrderIterator end_post_order();  // End PostOrder Iterator

        // Method to transform the tree into a min-heap and return an iterator
        typename Tree<T, K>::BFSIterator myHeap(); // Transform tree into a min-heap and return iterator        
        
    private:
        Node* root;  // Root node - field

        // Helper functions to display the tree
        void displayHelper(Node* node, int indent) const;
        
        // Helper functions to clear the tree - delete every node in the Tree.
        void clear(Node* node);

        // Helper function to draw the tree
        void drawNode(sf::RenderWindow& window, Node* node, sf::Vector2f position, float angle, float distance, int depth) const;

        // Helper function to draw the arrow
        void drawArrow(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end) const;  // Add this line
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
        std::queue<Node*> queue; // Queue to store the nodes according to BFS
    };

    // Define the DFSIterator class
    template <typename T, size_t K>
    class Tree<T, K>::DFSIterator {
    public:
        DFSIterator(Node* root);  // DFSIterator constructor
        DFSIterator(); // Default constructor
    
        // Overloaded operators
        bool operator!=(const DFSIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        DFSIterator& operator++();  // Increment operator

        void DFSAlgo(Node* root); // Helper function to perform DFS
        std::stack<Node*> getStack() const; // Method to access the stack (needed for conversion constructors)

    private:
        std::stack<Node*> stack;  // Stack to store the nodes according to DFS
    };

    // PreOrderIterator class - root, left, right
    template <typename T, size_t K>
    class Tree<T, K>::PreOrderIterator {
    public:
        PreOrderIterator(Node* root);  // PreOrderIterator constructor

        // Overloaded operators
        bool operator!=(const PreOrderIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        PreOrderIterator& operator++();  // Increment operator

    private:
        std::stack<Node*> stack;  // Stack to store the nodes according to Pre-Order
        DFSIterator dfs;  // DFSIterator object
    };

    // InOrderIterator class - left, root, right
    template <typename T, size_t K>
    class Tree<T, K>::InOrderIterator {
    public:
        InOrderIterator(Node* root);  // InOrderIterator constructor

        // Overloaded operators
        bool operator!=(const InOrderIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        InOrderIterator& operator++();  // Increment operator

    private:
        std::stack<Node*> stack;  // Stack to store the nodes according to InOrder
        DFSIterator dfs;  // DFSIterator object
        void pushLeft(Node* node);  // Helper function to arrange the nodes in the stack
    };

    // PostOrderIterator class - left, right, root
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
        DFSIterator dfs;  // DFSIterator object
        void pushLeft(Node* node);  // Helper function to push the left nodes to the stack

    };


    // ********** Implementations **********


    //Constructor template
    template <typename T, size_t K>
    Tree<T, K>::Tree() : root(nullptr) {}

    //Destructor template
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

    // Draw the nodes as circle with the its key represented by string - GUI
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

    // Define how to represent the direction of n edge with arrow - GUI
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

    // Define the begin of BFS - begin in the root of the tree
    template <typename T, size_t K>
    typename Tree<T, K>::BFSIterator Tree<T, K>::begin_bfs() {
        return BFSIterator(root);
    }

    // Define the end of BFS - end when its nullptr
    template <typename T, size_t K>
    typename Tree<T, K>::BFSIterator Tree<T, K>::end_bfs() {
        return BFSIterator(nullptr);
    }
    // Define the begin of DFS - being in the root of the tree
    template <typename T, size_t K>
    typename Tree<T, K>::DFSIterator Tree<T, K>::begin_dfs() {
        return DFSIterator(root);
    }

    // Define the end of DFS - end when its nullptr
    template <typename T, size_t K>
    typename Tree<T, K>::DFSIterator Tree<T, K>::end_dfs() {
        return DFSIterator(nullptr);
    }

    // Define the begin of PreOrder - begin in the root of the tree
    template <typename T, size_t K>
    typename Tree<T, K>::PreOrderIterator Tree<T, K>::begin_pre_order() {
        return PreOrderIterator(root);
    }

    // Define the end of PreOrder - end when its nullptr
    template <typename T, size_t K>
    typename Tree<T, K>::PreOrderIterator Tree<T, K>::end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    // Define the begin of InOrder - begin in the root of the tree
    template <typename T, size_t K>
    typename Tree<T, K>::InOrderIterator Tree<T, K>::begin_in_order() {
        return InOrderIterator(root);
    }

    // Define the end of InOrder - end when its nullptr
    template <typename T, size_t K>
    typename Tree<T, K>::InOrderIterator Tree<T, K>::end_in_order() {
        return InOrderIterator(nullptr);
    }

    // Define the begin of PostOrder - begin in the root of the tree
    template <typename T, size_t K>
    typename Tree<T, K>::PostOrderIterator Tree<T, K>::begin_post_order() {
        return PostOrderIterator(root);
    }

    // Define the end of PostOrder - end when its nullptr
    template <typename T, size_t K>
    typename Tree<T, K>::PostOrderIterator Tree<T, K>::end_post_order() {
        return PostOrderIterator(nullptr);
    }

    // insert the tree data to a vector and use make_heap to get iterator of min-heap
    // rebuild the tree a minimum heap and return iterator of BFS of the new tree
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

    // BFSIterator - root, left, right
    template <typename T, size_t K>
    Tree<T, K>::BFSIterator::BFSIterator(Node* root) {
        if (root) {
            queue.push(root);
        }
    }
 
    template <typename T, size_t K>
    bool Tree<T, K>::BFSIterator::operator!=(const BFSIterator& other) const {
        return queue != other.queue;
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

    // DFSIterator - Constructor
    //default constructor - used for K != 2 Cases
    //Iterator return the nodes in DFS according to the discovery time
    template <typename T, size_t K>
    Tree<T, K>::DFSIterator::DFSIterator(){}

    // Constructor
    template <typename T, size_t K>
    Tree<T, K>::DFSIterator::DFSIterator(Node* root){
        if (root) {
            stack.push(root);
        }
    }

    template <typename T, size_t K>
    bool Tree<T, K>::DFSIterator::operator!=(const DFSIterator &other) const
    {
        return stack != other.stack;
    }

    template <typename T, size_t K>
    const T& Tree<T, K>::DFSIterator::operator*() const {
        return stack.top()->key;
    }

    template <typename T, size_t K>
    typename Tree<T, K>::DFSIterator& Tree<T, K>::DFSIterator::operator++() {
        if (!stack.empty()) {
                Node* current = stack.top();
                stack.pop();
                for (int i = K-1; i >= 0; --i) {
                    if(current->children[i]){
                        stack.push(current->children[i]);
                    }
                }
        }
        return *this;
    }

    // Method to access the stack
    template <typename T, size_t K>
    std::stack<typename Tree<T, K>::Node*> Tree<T, K>::DFSIterator::getStack() const {
        return stack;
    }

    // PreOrderIterator - root, left, right
    template <typename T, size_t K>
    Tree<T, K>::PreOrderIterator::PreOrderIterator(Node* root) {
        if (root) {
            if(K == 2){
                stack.push(root);
            }
            else{
                dfs = DFSIterator(root);
                stack = dfs.getStack();
            }
        }else{
            root = nullptr;
        }
    }

    template <typename T, size_t K>
    bool Tree<T, K>::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
        return stack != other.stack;
    }

    template <typename T, size_t K>
    const T& Tree<T, K>::PreOrderIterator::operator*() const {
        return stack.top()->key;
    }

    template <typename T, size_t K>
    typename Tree<T, K>::PreOrderIterator& Tree<T, K>::PreOrderIterator::operator++() {
        Node* current = stack.top();
        stack.pop();
        for (size_t i = K; i-- > 0;) {  // Push children left to right
            if (current->children[i]) {
                stack.push(current->children[i]);
            }
        }
        return *this;
    }

    // InOrderIterator - left, root, right
    template <typename T, size_t K>
    Tree<T, K>::InOrderIterator::InOrderIterator(Node* root) {
        if(root){
            if(K == 2){
                pushLeft(root);  // init the stack with the left nodes
            }
            else{
                dfs = DFSIterator(root);
                stack = dfs.getStack();
            }
        }else{
            root = nullptr;
        }
    }

    //Not equal operator
    template <typename T, size_t K>
    bool Tree<T, K>::InOrderIterator::operator!=(const InOrderIterator& other) const {
        return stack != other.stack;
    }
    
    //Dereference operator
    template <typename T, size_t K>
    const T& Tree<T, K>::InOrderIterator::operator*() const {
        return stack.top()->key;
    }

    template <typename T, size_t K>
    typename Tree<T, K>::InOrderIterator& Tree<T, K>::InOrderIterator::operator++() {
        if(K == 2){
            Node* current = stack.top();
            stack.pop();
            pushLeft(current->children[1]);  // push the right child of the node
        }
        else{
            ++dfs;
            stack = dfs.getStack();
        }
        return *this;
    }

    template <typename T, size_t K>
    void Tree<T, K>::InOrderIterator::pushLeft(Node* node) {
        while (node) { 
            stack.push(node);
            node = node->children[0]; // go to the left most node
        }
    }

    // PostOrderIterator - left, right, root
    template <typename T, size_t K>
    Tree<T, K>::PostOrderIterator::PostOrderIterator(Node* root) {
        if(root){
            if(K == 2){ // if K is 2, run pushLeft to create stack in post-order
                pushLeft(root);
            
            }else{  // if K is not 2, use DFSIterator to create stack in DFS order
                dfs = DFSIterator(root);
                stack = dfs.getStack();
            }

        }else{
            root = nullptr;
        }
    }

    // Not equal operator - true if the stack is not empty
    template <typename T, size_t K>
    bool Tree<T, K>::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
        return stack != other.stack;
    }

    // Dereference operator - return the key of the top node in the stack
    template <typename T, size_t K>
    const T& Tree<T, K>::PostOrderIterator::operator*() const {
        return stack.top()->key;
    }

    // Increment operator - pop the top node in the stack
    template <typename T, size_t K>
    typename Tree<T, K>::PostOrderIterator& Tree<T, K>::PostOrderIterator::operator++() {
        if(K == 2){
            stack.pop();
        }else{
            ++dfs;
            stack = dfs.getStack();
        }
        return *this;
    }

    // Helper function to push nodes in post-order
    template <typename T, size_t K>
    void Tree<T, K>::PostOrderIterator::pushLeft(Node* node) {
        std::stack<Node*> tempStack;
        tempStack.push(node);
        
        while (!tempStack.empty()) {
            Node* current = tempStack.top();
            tempStack.pop();
            stack.push(current);

            // Push children to the temporary stack
            for (size_t i = 0; i < K; ++i) {
                if (current->children[i]) {
                    tempStack.push(current->children[i]);
                }
            }
        }

    }
} 


#endif 
