
// COS30008, Problem Set 4, Problem 1, 2022

#pragma once

#include <stdexcept>
#include <algorithm>

template<typename T>
struct BinaryTreeNode
{
    using BNode = BinaryTreeNode<T>; //BNode represents the btree 
    using BTreeNode = BNode*; //BtreeNode represents the pointer 
    
    T key; //data
    BTreeNode left;
    BTreeNode right;
    
    static BNode NIL;
    
    const T& findMax() const
    {
        if ( empty() )
        {
            throw std::domain_error( "Empty tree encountered." );
        }
        
        return right->empty() ? key : right->findMax(); // if right is empty then return the node, otherwise keep going
    }

    const T& findMin() const 
    {
        if ( empty() )
        {
            throw std::domain_error( "Empty tree encountered." );
        }
        
        return left->empty() ? key : left->findMin(); // if left is empty then return the node, otherwise keep going
    }

    bool remove( const T& aKey, BTreeNode aParent )
    {
        BTreeNode x = this; // BNode<S>* x
        BTreeNode y = aParent;

        while ( !x->empty() ) //while current node is not empty
        {
            if ( aKey == x->key ) //if the given key matches the node we break
            {
                break;
            }

            y = x;                                      // new parent (current node becomes the parent)
            
            x = aKey < x->key ? x->left : x->right;         //ternary for if the given key is less than current then its set to left, otherwise set to right
        }

        if ( x->empty() )
        {
            return false;                               // delete failed
        }
        
        if ( !x->left->empty() )
        {
            const T& lKey = x->left->findMax();         // find max to left
            x->key = lKey;
            x->left->remove( lKey, x );
        }
        else
        {
            if ( !x->right->empty() )
            {
                const T& lKey = x->right->findMin();    // find min to right
                x->key = lKey;
                x->right->remove( lKey, x );
            }
            else
            {
                if ( y != &NIL )                        // y can be NIL
                {
                    if ( y->left == x )
                    {
                        y->left = &NIL;
                    }
                    else
                    {
                        y->right = &NIL;
                    }
                }
                
                delete x;                               // free deleted node
            }
        }

        return true;
    }

    // PS4 starts here
    
    
    ~BinaryTreeNode()
    {
        if (!empty()) 
        {
            if (left != &NIL)
            {
                delete left;
            }
            if (right != &NIL)
            {
                delete right;
            }
        }
    }

    const bool empty()
    {
        return this == &NIL;
    }

    const bool leaf()
     {
         return left == &NIL && right == &NIL;
     }


    const size_t height()
    {
        if (empty()) 
        {
            throw std::domain_error("Empty tree encountered.");
        }

        if (leaf())
        {
            return 0;
        }  

        size_t left_side = 0;
        try {
            left_side = this->left->height(); //get the max height of the left subtree recursively(could also do it iteratively)
        }
        catch(domain_error e) {
            left_side = 0;
        }

        size_t right_side = 0;
        try {
             right_side = this->right->height(); //get the max height of the right subtree
        }
        catch (domain_error e) {
            right_side = 0;
        }
   
        if (left_side > right_side) //compare which side is higher + 1  and return max height
        {
            return left_side + 1; 
        }
        else
        {
            return right_side + 1;
        }
    }

    const size_t max(size_t left, size_t right)
    {
        if (left > right) {
            return left;
        }
        return right;
    }


    bool insert(const T& aKey)
    {
        BTreeNode x = this;  //  BTreeNode x == BNode<S>* x
        BTreeNode y = &NIL;

        while (!x->empty()) //if root node is NOT empty
        {
            y = x;  //copy it into y

            if (aKey == x->key) // if there is a duplicate key then theres an error
            {
                return false;
            }

            x = aKey < x->key ? x->left : x->right; //otherwise if the key is less than current insert to left otherwise to the right
        }

        BTreeNode z = new BinaryTreeNode(aKey);

        if (y->empty())
        {
            return false;   // if y is empty x was empty, insertion will fail(NIL)
        }
        else
        {
            if (aKey < y->key)  //if given key is less than current key, insert left
            {
                y->left = z;
            }
            else
            {
                y->right = z; //otherwise insert right
            }
        }
        return true;
    }

    BinaryTreeNode() :
        key(T()), 
        left(&NIL),
        right(&NIL)
    {}

    BinaryTreeNode(const T& aKey): 
        key(aKey), 
        left(&NIL),
        right(&NIL)
    {}

    BinaryTreeNode(T&& aKey) 
        :
        key(std::move(aKey)),
        left(&NIL),
        right(&NIL)
    {}
};

template<typename T>
BinaryTreeNode<T> BinaryTreeNode<T>::NIL;


