// Amber Mickler
// COP4530 Section 2
// Assignment 4
// Binary Expression Tree Header Definitions

#include "BET.h"
#include <stack>
#include <sstream>

    /* PRIVATE */

void BET::printInfixExpression(BinaryNode *n) const {
    bool parens;
    if (n == nullptr)
        return;
    if (n->left != nullptr) {
        // if left child is a lower precedence operator we need parens
        if ((n->left->element == "+" || n->left->element == "-") && (n->element == "*" || n->element == "/")) {
            cout << "( ";
            parens = true;
        }
        printInfixExpression(n->left);
        if (parens){
            cout << ") ";
            parens = false;
        }
    }
    cout << n->element << " ";
    if (n->right != nullptr) {
        // if right child is an operator of equal or lesser precedence we need parens
        if ((n->element == "*" || n->element == "/") &&
            (n->right->element == "+" || n->right->element == "-" || n->right->element == "*" || n->right->element == "/")) {
            cout << "( ";
            parens = true;
        }
        printInfixExpression(n->right);
        if (parens) {
            cout << ") ";
            parens = false;
        }
    }
}   // print to the standard output the corresponding infix expression

void BET::makeEmpty(BinaryNode* &t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}   // delete all nodes in the subtree pointed to by t

typename BET::BinaryNode * BET::clone(BinaryNode *t) {
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode{ t->element, clone(t->left), clone(t->right)};
}   // clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator=

void BET::printPostfixExpression(BinaryNode *n) const {
    if (n == nullptr)
        return;
    if (n->left != nullptr)
        printPostfixExpression(n->left);
    if (n->right != nullptr)
        printPostfixExpression(n->right);
    cout << n->element << " ";
}   // print to the standard output the corresponding postfix expression

size_t BET::size(BinaryNode *t) const {
    if (t == nullptr)
        return 0;
    return (size(t->left) + 1 + size(t->right));

}   // return the number of nodes in the subtree pointed to by t

size_t BET::leaf_nodes(BinaryNode *t) const {
    if (t == nullptr)
        return 0;
    if (t->left == nullptr && t->right == nullptr)
        return 1;
    else
        return leaf_nodes(t->left) + leaf_nodes(t->right);
}   // return the number of leaf nodes in the subtree pointed to by t


    /* PUBLIC */

BET::BET() {
    root = nullptr;
}   // default zero-parameter constructor, Builds an empty tree

BET::BET(const string& postfix) {
    string psf = postfix;
    stack<BinaryNode> stk;
    BinaryNode * op1;
    BinaryNode * op2;
    int operatorCount = 0;
    int operandCount = 0;
    bool syntax = false;
    istringstream stream (psf);
    stream >> psf;
    while (stream) {
        if (psf == "+" || psf ==  "-" || psf == "*" || psf == "/") {
            if (!syntax)
                break;
            operatorCount++;
            if (stk.size() < 2)
                break;
            op2 = new BinaryNode(stk.top().element, stk.top().left, stk.top().right);
            stk.pop();
            op1 = new BinaryNode(stk.top().element, stk.top().left, stk.top().right);
            stk.pop();
            BinaryNode n(psf, op1, op2);
            stk.push(n);
        }
        else {
            BinaryNode n = BinaryNode(psf, nullptr, nullptr);
            stk.push(n);
            operandCount++;
            if (operandCount > 1)
                syntax = true;
        }
        stream >> psf;
    }
    if (++operatorCount != operandCount)
        syntax = false;
    if (!syntax) {
        cout << "Wrong postfix expression." << endl;
        root = nullptr;
    }
    else
        root = new BinaryNode(stk.top().element, stk.top().left, stk.top().right);
}   // "postfix" is string containing a postfix expression separated by spaces

BET::BET(const BET& tree) : root{nullptr} {
    root = clone(tree.root);
}   // copy constructor -- makes appropriate deep copy of the tree

BET::~BET() {
    makeEmpty(root);
    delete root;
}   // destructor -- cleans up all dynamic space in the tree

bool BET::buildFromPostfix(const string& postfix) {
    makeEmpty(root);
    *this = BET(postfix);
    return (root != nullptr);
}   // delete any existing nodes & Return true if the new tree is built successfully

const BET & BET::operator= (const BET& tree) {
    root = clone(tree.root);
    return *this;
}   // assignment operator -- makes appropriate deep copy

void BET::printInfixExpression() const {
    printInfixExpression(root);
    cout << endl;
}   // Print out the infix expression. Should do this by making use of the private (recursive) version

void BET::printPostfixExpression() const {
    printPostfixExpression(root);
    cout << endl;
}   // Print the postfix form of the expression. Use the private recursive function to help

size_t BET::size() const {
    return size(root);
}   // Return the number of nodes in the tree (using the private recursive function)

size_t BET::leaf_nodes() const {
    return leaf_nodes(root);
}   // Return the number of leaf nodes in the tree. (Use the private recursive function to help)

bool BET::empty() const {
    return (root == nullptr);
}   // return true if the tree is empty. Return false otherwise.
