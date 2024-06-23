#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Complex.hpp"
#include "Tree.hpp"

TEST_CASE("Complex Number Constructor Default") {
    Complex c1;
    CHECK(c1.re() == doctest::Approx(0));
    CHECK(c1.im() == doctest::Approx(0));
}

TEST_CASE("Complex Number Constructor with Parameters") {
    Complex c1(3, 4);
    CHECK(c1.re() == doctest::Approx(3));
    CHECK(c1.im() == doctest::Approx(4));
}

TEST_CASE("Complex Number Unary Operator NOT") {
    Complex c1(0, 0);
    CHECK(!c1 == true);
}

TEST_CASE("Complex Number Unary Operator Minus") {
    Complex c2(3, -4);
    Complex c3 = -c2;
    CHECK(c3.re() == doctest::Approx(-3));
    CHECK(c3.im() == doctest::Approx(4));
}

TEST_CASE("Complex Number Binary Operator Plus") {
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex c3 = c1 + c2;
    CHECK(c3.re() == doctest::Approx(4));
    CHECK(c3.im() == doctest::Approx(6));
}

TEST_CASE("Complex Number Binary Operator Plus Equals") {
    Complex c1(1, 2);
    Complex c2(3, 4);
    c1 += c2;
    CHECK(c1.re() == doctest::Approx(4));
    CHECK(c1.im() == doctest::Approx(6));
}

TEST_CASE("Complex Number Binary Operator Minus Equals") {
    Complex c1(4, 6);
    Complex c4(5, 6);
    c1 -= c4;
    CHECK(c1.re() == doctest::Approx(-1));
    CHECK(c1.im() == doctest::Approx(0));
}

TEST_CASE("Complex Number Binary Operator Multiply Equals") {
    Complex c5(1, 1);
    Complex c6(2, 2);
    c5 *= c6;
    CHECK(c5.re() == doctest::Approx(0));
    CHECK(c5.im() == doctest::Approx(4));
}

TEST_CASE("Complex Number Prefix Increment") {
    Complex c1(0, 0);
    ++c1;
    CHECK(c1.re() == doctest::Approx(1));
    CHECK(c1.im() == doctest::Approx(0));
}

TEST_CASE("Complex Number Postfix Increment") {
    Complex c2(0, 0);
    Complex c3 = c2++;
    CHECK(c2.re() == doctest::Approx(1));
    CHECK(c2.im() == doctest::Approx(0));
    CHECK(c3.re() == doctest::Approx(0));
    CHECK(c3.im() == doctest::Approx(0));
}

TEST_CASE("Complex Number Comparison Less Than") {
    Complex c1(3, 4); // Magnitude = 5
    Complex c2(5, 12); // Magnitude = 13
    CHECK(c1 < c2);
}

TEST_CASE("Complex Number Comparison Greater Than") {
    Complex c1(3, 4); // Magnitude = 5
    Complex c2(5, 12); // Magnitude = 13
    CHECK(c2 > c1);
}

TEST_CASE("Complex Number Equality") {
    Complex c1(1.0001, 2.0001);
    Complex c2(1.0001, 2.0001);
    CHECK(c1 == c2);
}

TEST_CASE("Complex Number Inequality") {
    Complex c1(1.0001, 2.0001);
    Complex c3(1.002, 2.002);
    CHECK(c1 != c3);
}

TEST_CASE("Complex Number Stream Output Operator") {
    std::stringstream ss;
    Complex c1(3, 4);
    ss << c1;
    CHECK(ss.str() == "3+4i");
}

TEST_CASE("Complex Number Stream Input Operator") {
    std::stringstream ss;
    Complex c2;
    ss.str("5-6i");
    ss >> c2;
    CHECK(c2.re() == doctest::Approx(5));
    CHECK(c2.im() == doctest::Approx(-6));
}

TEST_CASE("Tree Constructor and Add Root") {
    ariel::Tree<int> tree;
    CHECK_NOTHROW(tree.add_root(1));
}

TEST_CASE("Tree Add Sub Node") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    CHECK_NOTHROW(tree.add_sub_node(tree.get_root(), 2));
    CHECK_NOTHROW(tree.add_sub_node(tree.get_root(), 3));
}

TEST_CASE("Tree BFS Iterator") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    auto it = tree.begin_bfs();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
}

TEST_CASE("Tree DFS Iterator") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    auto it = tree.begin_dfs();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2 ); // Depending on the implementation, DFS can visit the left or right child first
}

TEST_CASE("Tree PreOrder Iterator") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    auto it = tree.begin_preorder();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
}

TEST_CASE("Tree InOrder Iterator") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    auto it = tree.begin_inorder();
    CHECK(*it == 2); // In a binary tree, the inorder traversal visits the left child, then the root, then the right child
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 3);
}

TEST_CASE("Tree PostOrder Iterator") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    auto it = tree.begin_postorder();
    CHECK(*it == 3); // In a binary tree, the postorder traversal visits the children first, then the root
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
}

TEST_CASE("Tree Display") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    CHECK_NOTHROW(tree.display());
}

