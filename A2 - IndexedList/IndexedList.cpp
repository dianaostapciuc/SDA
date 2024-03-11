#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"
using namespace std;
IndexedList::IndexedList() {
    this->head = nullptr;
    this->size_list = 0;
}
//Theta(1)

int IndexedList::size() const
{
    return this->size_list;
}
//Theta(1)

bool IndexedList::isEmpty() const {
    if (this->size_list == 0)
        return true;
	return false;
}
//Theta(1)

TElem IndexedList::getElement(int pos) const {
    if (pos < 0 or pos > this->size_list)
        throw exception();
    PNode current = this->head;
    for (int i = 0; i < pos; i++)
        current = current->next; // we find our current elem
    return current->info;
}
//BEST case: Theta(1) (when it's the first element), WORST case: Theta(size_list) (when it's the last element), TOTAL: O(size_list)

TElem IndexedList::setElement(int pos, TElem e) {
    if (pos < 0 or pos > this->size_list)
        throw exception();
    PNode current = this->head;
    for (int i = 0; i < pos; i++)
        current = current->next;
    TElem old_value = current->info;
    current->info = e;
    return old_value;
}
//BEST case: Theta(1) (when it's the first element), WORST case: Theta(size_list) (when it's the last element), TOTAL: O(size_list)


void IndexedList::addToEnd(TElem e) {
    addToPosition(this->size_list, e);
}
//BEST case: Theta(1), WORST case: Theta(size_list), TOTAL: O(size_list)

void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0 or pos > this->size_list)
        throw exception();
    PNode new_node = new SLLNode(e, nullptr); // creating a new node

    if (pos == 0) //means we gotta add it at the beginning
    {
        new_node->next = this->head;
        this->head = new_node; // the head becomes the added node
    }
    else
    {
        PNode current = this->head;
        for (int i = 0; i < pos - 1; i++)
            current = current->next; // find the elem before the one where we add so we can add the new one in between
        new_node->next = current->next;
        current->next = new_node;
        if (pos == this->size_list) // in case we add on the last position
            new_node->next = nullptr;
    }
    this->size_list++; // increasing size of list
}
//BEST case: Theta(1) (when we add on the first position), WORST case: Theta(size_list) (when we add on the last position), TOTAL: O(size_list)

TElem IndexedList::remove(int pos) {
    if (pos < 0 or pos >= this->size_list)
        throw exception();
    PNode current = this->head;
    PNode previous = nullptr;
    for (int i = 0; i < pos; i++) {
        previous = current;
        current = current->next; // find the node to remove
    }
    if (previous == nullptr) // if it's the first node
        this->head = current->next;
    else if (current->next == nullptr) // if it's the last
        previous->next = nullptr;
    else
        previous->next = current->next; // if it's a random one

    TElem removed_element = current->info;
    delete current;
    this->size_list--;
    return removed_element;
}
//BEST case: Theta(1) (removing the first elem), WORST case: Theta(size_list) (removing the last), TOTAL: O(size_list)

TPosition IndexedList::lastIndexOf(TElem elem) const
{
    PNode current = this->head;
    int last_position = -1;
    for (int i = 0; i<this->size_list; i++)
    {
        if (current->info == elem)
            last_position = i;
        current = current->next;
    }
    if (last_position != -1)
        return last_position;
    else return -1;
}
//BEST = WORST case: Theta(size_list), TOTAL: O(size_list)

int IndexedList::search(TElem e) const{
    PNode current = this->head;
    for (int i = 0; i<this->size_list; i++)
    {
        if (current->info == e)
            return i;
        current = current->next;
    }
	return -1;
}
// BEST case: Theta(1) (when we're searching for the first element), WORST case: Theta(size_list) (when we're searching for the last elem)
// TOTAL: O(size_list)

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

IndexedList::~IndexedList() {
    PNode current = this->head;
    while (current != nullptr)
    {
        PNode next = current->next;
        delete current;
        current = next;
    }
}
//BEST case: Theta(1), WORST case: Theta(size_list), TOTAL: O(size_list)