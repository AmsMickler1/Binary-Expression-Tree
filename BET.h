// Amber Mickler
// COP4530 Section 2
// Assignment 4
// Binary Expression Tree Header


#ifndef BET_H
#define BET_H

#include <iostream>
#include <string>
using namespace std;

    class BET{

    private:        // ALL OF THESE MUST BE IMPLEMENTED RECURSIVELY

    struct BinaryNode {
        string element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const string & el, BinaryNode *lt, BinaryNode *rt) : element{el}, left{lt}, right{rt} { }
        BinaryNode(string && el, BinaryNode *lt, BinaryNode *rt) : element{std::move(el)}, left{lt}, right{rt} { }
        };

        BinaryNode* root;

        void printInfixExpression(BinaryNode *n) const;     // print to the standard output the corresponding infix expression
        void makeEmpty(BinaryNode* &t);                     // delete all nodes in the subtree pointed to by t
        BinaryNode * clone(BinaryNode *t);                  // clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator=
        void printPostfixExpression(BinaryNode *n) const;   // print to the standard output the corresponding postfix expression
        size_t size(BinaryNode *t) const;                   // return the number of nodes in the subtree pointed to by t
        size_t leaf_nodes(BinaryNode *t) const;             // return the number of leaf nodes in the subtree pointed to by t



    public:
        BET();                                          // default zero-parameter constructor, Builds an empty tree
        BET(const string& postfix);                     // "postfix" is string containing a postfix expression separated by spaces
        BET(const BET&);                                // copy constructor -- makes appropriate deep copy of the tree
        ~BET();                                         // destructor -- cleans up all dynamic space in the tree
        bool buildFromPostfix(const string& postfix);   // delete any existing nodes & Return true if the new tree is built successfully
        const BET & operator= (const BET &);            // assignment operator -- makes appropriate deep copy
        void printInfixExpression() const;              // Print out the infix expression. Should do this by making use of the private (recursive) version
        void printPostfixExpression() const;            // Print the postfix form of the expression. Use the private recursive function to help
        size_t size() const;                            // Return the number of nodes in the tree (using the private recursive function)
        size_t leaf_nodes() const;                      // Return the number of leaf nodes in the tree. (Use the private recursive function to help)
        bool empty() const;                             // return true if the tree is empty. Return false otherwise.

    }; // end of class BET

    #include "BET.hpp"

//Make sure to declare as const member functions any for which this is appropriate

#endif
