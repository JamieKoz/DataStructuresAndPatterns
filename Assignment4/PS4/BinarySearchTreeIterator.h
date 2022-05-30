
// COS30008, Problem Set 4, Problem 3, 2022

#pragma once

#include "BinarySearchTree.h"

#include <stack>

template<typename T>
class BinarySearchTreeIterator
{
private:
    
    using BSTree = BinarySearchTree<T>;
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    using BTNStack = std::stack<BTreeNode>;

    const BSTree& fBSTree;		// binary search tree
    BTNStack fStack;			// DFS traversal stack
    
    void pushLeft(BTreeNode aNode) {
        while (!aNode->empty())
        {
            if (!fBSTree.fRoot->empty())
            {
                fStack.push(aNode); // pushes aNode to the root
                fBSTree.fRoot = fBSTree.fRoot->left; // makes root = left node
            }
        }

    }
    
public:
    
    using Iterator = BinarySearchTreeIterator<T>;
    
    BinarySearchTreeIterator(const BSTree& aBSTree)
        :
        fBSTree(&BNode::NIL),
        fStack(&BNode::NIL)
    {

    }

    const T& operator*() const //get key
    {
        if (fStack.empty() == false)
        {
            return fStack.top();
        }
    }

    Iterator& operator++() 
    {
        if ( fStack.empty() == false)
        {
            fStack.pop();
            //fBSTree = fBSTree.fRoot->right;
            return *this;
        }
    }

    Iterator operator++(int)
    {
        BinarySearchTreeIterator temp = *this; 
        ++(*this); 
        return temp;
    }

    bool operator==( const Iterator& aOtherIter ) const
    {
        return fStack.size() == aOtherIter.fStack.size();
    }

    bool operator!=(const Iterator& aOtherIter) const 
    {
        return !(*this == aOtherIter);
    }
    
    Iterator begin() const {
        return BinarySearchTreeIterator<T>(*this);
    }
    Iterator end() const
    {
        return begin().end();
    }
};
