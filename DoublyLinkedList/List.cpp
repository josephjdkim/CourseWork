//  Doubly Linked List
//  (Recitation 12 for Object Oriented Programming under Prof. John Sterling)
//
//  Copyright © 2017 Joe Kim. All rights reserved.

#include <cstdlib>
#include <iostream>
#include "List.hpp"
using namespace std;

List::Node::Node(int data, Node* prior, Node* next) :
data(data), prior(prior), next(next) {}
bool operator==(const List::Iterator& lhs, const List::Iterator& rhs) {
    return lhs.ptr == rhs.ptr;
}
List::Iterator::Iterator(Node* ptr) : ptr(ptr) {}
List::Iterator& List::Iterator::operator++() {
    ptr = ptr->next;
    return *this;
}
List::Iterator& List::Iterator::operator--() {
    ptr = ptr->prior;
    return *this;
}
int List::Iterator::operator*() const{
    return ptr->data;
}
int& List::Iterator::operator*() {
    return ptr->data;
}
List::List() : header(new Node(0, nullptr, nullptr)),
trailer(new Node(0, nullptr, nullptr)), lSize(0) {
    header->next = trailer;
    trailer->prior = header;
}
List::~List() {
    while(lSize) {
        pop_back();
    }
    delete header;
    delete trailer;
}
List::List(const List& rhs) : header(new Node(0, nullptr, nullptr)),
trailer(new Node(0, nullptr, nullptr)), lSize(0) {
    header->next = trailer;
    trailer->prior = header;
    for (size_t index = 0; index < rhs.size(); ++index) {
        push_back(rhs[index]);
    }
}
List& List::operator=(const List& rhs) {
    if (this != &rhs) {
        while(lSize) {
            pop_back();
        }
        for (size_t index = 0; index < rhs.size(); ++index) {
            push_back(rhs[index]);
        }
    }
    return *this;
}
int List::front() { return header->next->data; }
int List::back() { return trailer->prior->data; }
size_t List::size() const { return lSize; }
void List::push_back(int d) {
    trailer->prior->next = new Node(d, trailer->prior, trailer);
    trailer->prior = trailer->prior->next;
    ++lSize;
}
void List::push_front(int d) {
    header->next->prior = new Node(d, header, header->next);
    header->next = header->next->prior;
    ++lSize;
}
void List::pop_back() {
    if (lSize) {
        trailer->prior = trailer->prior->prior;
        delete trailer->prior->next;
        trailer->prior->next = trailer;
        --lSize;
    }
}
void List::pop_front() {
    if (lSize) {
        header->next = header->next->next;
        delete header->next->prior;
        header->next->prior = header;
        --lSize;
    }
}
void List::clear() {
    while (lSize) { pop_back(); }
}
int List::operator[](size_t index) const {
    size_t loc;
    Node* hp = header->next;
    for (loc = 0; loc < index; ++loc) {
        hp = hp->next;
    }
    return hp->data;
}
int& List::operator[](size_t index) {
    size_t loc;
    Node* hp = header->next;
    for (loc = 0; loc < index; ++loc) {
        hp = hp->next;
    }
    return hp->data;
}
List::Iterator List::begin() const { return Iterator(header->next); }
List::Iterator List::end() const { return Iterator(trailer); }
List::Iterator List::insert(Iterator loc, int d) {
    loc.ptr->prior->next = new Node(d, loc.ptr->prior, loc.ptr);
    loc.ptr->prior = loc.ptr->prior->next;
    ++lSize;
    return Iterator(loc.ptr->prior);
}
List::Iterator List::erase(Iterator loc) {
    Iterator nextLoc(loc);
    ++nextLoc;
    nextLoc.ptr->prior = loc.ptr->prior;
    nextLoc.ptr->prior->next = nextLoc.ptr;
    delete loc.ptr;
    --lSize;
    return nextLoc;
}

bool operator!=(const List::Iterator& lhs, const List::Iterator& rhs) {
    return !(lhs==rhs);
}

ostream& operator<<(ostream& os, const List& rhs) {
    List::Node* hp = rhs.header->next;
    while (hp->next) {
        os << hp->data << ' ';
        hp = hp->next;
    }
    return os;
}
