//  Doubly Linked List
//  (Recitation 12 for Object Oriented Programming under Prof. John Sterling)
//  Single Compilation File with test code and solutions at bottom
//
//  Copyright © 2017 Joe Kim. All rights reserved.

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& rhs);
    struct Node {
        Node(int data=0, Node* prior = nullptr, Node* next = nullptr) :
        data(data), prior(prior), next(next) {}
        int data;
        Node* next;
        Node* prior;
    };
public:
    class Iterator {
        friend class List;
        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.ptr == rhs.ptr;
        }
    public:
        Iterator(Node* ptr=nullptr) : ptr(ptr) {}
        Iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        Iterator& operator--() {
            ptr = ptr->prior;
            return *this;
        }
        int operator*() const{
            return ptr->data;
        }
        int& operator*() {
            return ptr->data;
        }
    private:
        Node* ptr;
    }; // end of Iterator class
    
    List() : header(new Node(0, nullptr, nullptr)),
    trailer(new Node(0, nullptr, nullptr)), lSize(0) {
        header->next = trailer;
        trailer->prior = header;
    }
    ~List() {
        while(lSize) {
            pop_back();
        }
        delete header;
        delete trailer;
    }
    List(const List& rhs) : header(new Node(0, nullptr, nullptr)),
    trailer(new Node(0, nullptr, nullptr)), lSize(0) {
        header->next = trailer;
        trailer->prior = header;
        for (size_t index = 0; index < rhs.size(); ++index) {
            push_back(rhs[index]);
        }
    }
    List& operator=(const List& rhs) {
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
    int front() { return header->next->data; }
    int back() { return trailer->prior->data; }
    size_t size() const { return lSize; }
    void push_back(int d) {
        trailer->prior->next = new Node(d, trailer->prior, trailer);
        trailer->prior = trailer->prior->next;
        ++lSize;
    }
    void push_front(int d) {
        header->next->prior = new Node(d, header, header->next);
        header->next = header->next->prior;
        ++lSize;
    }
    void pop_back() {
        if (lSize) {
            trailer->prior = trailer->prior->prior;
            delete trailer->prior->next;
            trailer->prior->next = trailer;
            --lSize;
        }
    }
    void pop_front() {
        if (lSize) {
            header->next = header->next->next;
            delete header->next->prior;
            header->next->prior = header;
            --lSize;
        }
    }
    void clear() {
        while (lSize) { pop_back(); }
    }
    int operator[](size_t index) const {
        size_t loc;
        Node* hp = header->next;
        for (loc = 0; loc < index; ++loc) {
            hp = hp->next;
        }
        return hp->data;
    }
    int& operator[](size_t index) {
        size_t loc;
        Node* hp = header->next;
        for (loc = 0; loc < index; ++loc) {
            hp = hp->next;
        }
        return hp->data;
    }
    Iterator begin() const { return Iterator(header->next); }
    Iterator end() const { return Iterator(trailer); }
    Iterator insert(Iterator loc, int d) {
        loc.ptr->prior->next = new Node(d, loc.ptr->prior, loc.ptr);
        loc.ptr->prior = loc.ptr->prior->next;
        ++lSize;
        return Iterator(loc.ptr->prior);
    }
    Iterator erase(Iterator loc) {
        Iterator nextLoc(loc);
        ++nextLoc;
        nextLoc.ptr->prior = loc.ptr->prior;
        nextLoc.ptr->prior->next = nextLoc.ptr;
        delete loc.ptr;
        --lSize;
        return nextLoc;
    }
private:
    size_t lSize;
    Node* header;
    Node* trailer;
};

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


// THE BELOW CODE IS FOR TESTING THE LIST AND MEETING THE LAB ASSIGNMENT'S
// REQUIREMENTS. IT DEMONSTRATES PROPERTIES AND FUNCTIONS OF THE LIST.


void printListInfo(List& myList) {
    cout << "size: " << myList.size()
    << ", front: " << myList.front()
    << ", back(): " << myList.back()
    << ", list: " << myList << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {
    
    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
    << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
