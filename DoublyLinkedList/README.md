# Doubly Linked List
## A bit about the code
This is my solution to an implementation of a doubly linked list for one of Professor John Sterling's labs.

The List has a private Node struct. All Nodes have three fields - integer data, a prior pointer, and a next pointer. My List is implemented with sentinel nodes - a header and trailer - making the code simpler for traversal. The header's prior as well as the trailer's next are always nullptrs. They both also hold an arbitrary data value (0) that is completely junk data.

In the case of an empty List, the header's next would point to the trailer, and the trailer's prior would point to the header.

The List has some standard methods such as:
```C++
void push_back(int d);
void push_front(int d);
void pop_back();
void pop_front();
size_t size();
int front();
int back();
void clear();
```
The List class has an index operator for traversal, as well as an Iterator class implemented.

By using the Iterator class, the ```begin()``` and ```end()``` methods were implemented, returning Iterators with pointers to the first "real" node and the trailer node, respectively.

## Hindsight is 20/20
The part of my code that is glaringly painful for me is that I should have implemented the ```pop_back()``` and ```pop_front()``` methods so that they wouldn't delete the nodes that were being popped.

I implemented the pop methods under the assumption that the removed nodes would be useless and unneeded after removal (which was a rather silly assumption to make). Rather than completely deleting the node, simply taking it out of the list and then returning it may have been a better idea.