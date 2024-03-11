#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef int TPosition;
#define NULL_TELEM -11111
class ListIterator;

class IndexedList {
public:

    struct SLLNode;
    typedef SLLNode* PNode;
    struct SLLNode{
        TElem info;
        PNode next; // pointing to the next node
        SLLNode(TElem e, PNode n): info(e), next(n) {}
    };
    int size_list;
    PNode head;

	//DO NOT CHANGE THIS PART
    friend class ListIterator;    

    // constructor
    IndexedList ();

    TPosition lastIndexOf(TElem elem) const;

    // returns the number of elements from the list
    int size() const;

    // checks if the list is empty
    bool isEmpty() const;

    // returns an element from a position
    //throws exception if the position is not valid
    TElem getElement(int pos) const;

    // modifies an element from a given position
	//returns the old value from the position
    //throws an exception if the position is not valid
    TElem setElement(int pos, TElem e);

    // adds an element to the end of the list
    void addToEnd(TElem e);

    // adds an element to a given position
    //throws an exception if the position is not valid
    void addToPosition(int pos, TElem e);

    // removes an element from a given position
	//returns the removed element
    //throws an exception if the position is not valid
    TElem remove(int pos);

    // searches for an element and returns the first position where the element appears or -1 if the element is not in the list
    int search(TElem e)  const;

    // returns an iterator set to the first element of the list or invalid if the list is empty
    ListIterator iterator() const;

    //destructor
    ~IndexedList();

};
