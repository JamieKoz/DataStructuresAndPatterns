
// COS30008, List, Problem Set 3, 2022

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <stdexcept>

template<typename T>
class List
{
private:
    // auxiliary definition to simplify node usage
    using Node = DoublyLinkedList<T>;

    Node* fRoot;	// the first element in the list
    size_t fCount;	// number of elements in the list

public:
    // auxiliary definition to simplify iterator usage
    using Iterator = DoublyLinkedListIterator<T>;

	~List()                                                             // destructor - frees all nodes
    {
        while ( fRoot != nullptr )
        {
            if ( fRoot != &fRoot->getPrevious() )                       // more than one element
            {
                Node* lTemp = const_cast<Node*>(&fRoot->getPrevious()); // select last
                
                lTemp->isolate();                                       // remove from list
                delete lTemp;                                           // free
            }
            else
            {
                delete fRoot;                                           // free last
                break;                                                  // stop loop
            }
        }
    }

    void remove( const T& aElement )	                                // remove first match from list
    {
        Node* lNode = fRoot;                                            // start at first
        
        while ( lNode != nullptr )                                      // Are there still nodes available?
        {
            if ( **lNode == aElement )                                  // Have we found the node?
            {
                break;                                                  // stop the search
            }

            if ( lNode != &fRoot->getPrevious() )                       // not reached last
            {
                lNode = const_cast<Node*>(&lNode->getNext());           // go to next
            }
            else
            {
                lNode = nullptr;                                        // stop search
            }
        }
        
        // At this point we have either reached the end or found the node.
        if ( lNode != nullptr )                                         // We have found the node.
        {
            if ( fCount != 1 )                                          // not the last element
            {
                if ( lNode == fRoot )
                {
                    fRoot = const_cast<Node*>(&fRoot->getNext());       // make next root
                }
            }
            else
            {
                fRoot = nullptr;                                        // list becomes empty
            }
            
            lNode->isolate();                                           // isolate node
            delete lNode;                                               // release node's memory
            fCount--;                                                   // decrement count
        }
    }

	//////////////////////////////////////////////////////////////////
    //// PS3
    //////////////////////////////////////////////////////////////////
    
	// P1

    List() // default constructor
    {
        fCount = 0;
    }

    bool empty() const 
    {
        return fCount == 0;
    }	

    // Is list empty?
    size_t size() const 
    {
        return fCount;
    };                		// list size

    void push_front(const T& aElement) 
    {  
        Node* node = new Node(aElement);

        if (!empty()) {
            fRoot->push_front(*node);
        }

        fRoot = node;
        fCount++;
    }	   

    // return a forward iterator
    Iterator begin() const {
        return Iterator(fRoot).begin();
    }
    // return a forward end iterator
    Iterator end() const {
        return Iterator(fRoot).end();
    }
    // return a backwards iterator
    Iterator rbegin() const {
        return Iterator(fRoot).rbegin();
    }
    // return a backwards end iterator
    Iterator rend() const {    
        return Iterator(fRoot).rend();
    }
	// P2
    // 
     // adds aElement at back
    void push_back(const T& aElement) { 

        Node* node = new Node(aElement);


        if (!empty()) {
            fRoot->push_front(*node);
        }
        else {
            fRoot = node;
        }

       
        fCount++;
    }       

	// P3

    const T& operator[](size_t aIndex) const
    {
        if (aIndex >= fCount || aIndex < 0)
        {
            throw std::out_of_range("Index out of bounds.");
        }

        int currentIndex = 0;
        Iterator iter = begin();

        for (int i = 0; i != aIndex; i++) 
        {
            iter++;
        }

        return *iter;
    }

	// P4

    // copy constructor
    List(const List& aOtherList) 
    {
        for (const T& element : aOtherList)
        {
            this->push_back(element);
        }
    }; 

    // assignment operator
    List& operator=(const List& aOtherList) {

        if (&aOtherList != this) {

            this->~List();
            this->fCount = 0;

            for (const T& element : aOtherList)
            {
                this->push_back(element);
            }
        }
      
        return *this;
    }
    
	// P5

    // move constructor
    List(List&& aOtherList) {

        for (auto iter = aOtherList.begin(); iter != iter.end(); iter = aOtherList.begin())
        {
            auto val = *iter;
            this->push_back(std::move(val));
            aOtherList.remove(*iter);
        }
    }

    // move assignment operator
    List& operator=(List&& aOtherList) {
        if (&aOtherList != this) {

            this->~List();
            this->fCount = 0;

            for (auto iter = aOtherList.begin(); iter != iter.end(); iter = aOtherList.begin())
            {
                auto val = *iter;
                this->push_back(std::move(val));
                aOtherList.remove(*iter);
            }
        }

        return *this;
    }

    // move push_front
    void push_front(T&& aElement) {

        Node* node = new Node(std::move(aElement));

        if (!empty()) {
            fRoot->push_front(*node);
        }

        fRoot = node;
        fCount++;
    }

    // move push_back
    void push_back(T&& aElement) {
        Node* node = new Node(std::move(aElement));

        if (!empty()) {
            fRoot->push_front(*node);
        }
        else {
            fRoot = node;
        }

        fCount++;
    }				
};


