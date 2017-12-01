//  Doubly Linked List
//  (Recitation 12 for Object Oriented Programming under Prof. John Sterling)
//
//  Copyright © 2017 Joe Kim. All rights reserved.

#ifndef LIST_HPP

#include <cstdlib>
#include <iostream>

class List {
    friend std::ostream& operator<<(std::ostream& os, const List& rhs);
    struct Node {
        Node(int data=0, Node* prior = nullptr, Node* next = nullptr);
        int data;
        Node* next;
        Node* prior;
    };
public:
    class Iterator {
        friend class List;
        friend bool operator==(const Iterator& lhs, const Iterator& rhs);
    public:
        Iterator(Node* ptr=nullptr);
        Iterator& operator++();
        Iterator& operator--();
        int operator*() const;
        int& operator*();
    private:
        Node* ptr;
    }; // end of Iterator class
    
    List();
    ~List();
    List(const List& rhs);
    List& operator=(const List& rhs);
    int front();
    int back();
    size_t size() const;
    void push_back(int d);
    void push_front(int d);
    void pop_back();
    void pop_front();
    void clear();
    int operator[](size_t index) const;
    int& operator[](size_t index);
    Iterator begin() const;
    Iterator end() const;
    Iterator insert(Iterator loc, int d);
    Iterator erase(Iterator loc);
private:
    size_t lSize;
    Node* header;
    Node* trailer;
};

bool operator!=(const List::Iterator& lhs, const List::Iterator& rhs);

std::ostream& operator<<(std::ostream& os, const List& rhs);

#endif
