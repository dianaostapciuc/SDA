#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    this->capacity = 5;
    this->nr_elements = 0;
    this->nr_lines = nrLines;
    this->nr_columns = nrCols;
    this->root = -1;
    this->first_empty = 0;
    this->nodes = new Node[this->capacity];
    this->nodes[first_empty].left = 1;
    this->nodes[first_empty].right = -1;
    this->nodes[first_empty].parent = -1;

    get<2>(this->nodes[first_empty].info) = NULL_TELEM;
    for(int i = 1; i < this->capacity - 1; i++)
    {
        this->nodes[i].left = i + 1;
        this->nodes[i].right = -1;
        this->nodes[i].parent = -1;
        get<2>(this->nodes[i].info) = NULL_TELEM;
    }
    this->nodes[this->capacity - 1].right = -1;
    this->nodes[this->capacity - 1].left = -1;
    this->nodes[this->capacity - 1].parent = -1;
    get<2>(this->nodes[this->capacity - 1].info) = NULL_TELEM;

}
//BC = WC = O(capacity)

int Matrix::nrLines() const {
	return this->nr_lines;
}
//BC = WC = Theta(1)

int Matrix::nrColumns() const {
	return this->nr_columns;
}
//BC = WC = Theta(1)

TElem Matrix::element(int i, int j) const {
	if (i>=this->nr_lines or i < 0)
        throw exception();
    if (j>=this->nr_columns or j<0)
        throw exception();
    // checking if i and j are within the bounds of the matrix

    int current_node = this->root;
    while(current_node!=-1) // going through the nodes
    {
        if(get<0>(this->nodes[current_node].info) == i and get<1>(this->nodes[current_node].info) == j)
            return get<2>(this->nodes[current_node].info); // when it finds it
        if(get<0>(this->nodes[current_node].info) == i and get<1>(this->nodes[current_node].info) < j)
        {
            current_node = this->nodes[current_node].right;
        }
        else if(get<0>(this->nodes[current_node].info) < i)
        {
            current_node = this->nodes[current_node].right;
        }
        else if(get<0>(this->nodes[current_node].info) == i and get<1>(this->nodes[current_node].info) > j)
        {
            current_node = this->nodes[current_node].left;
        }
        else if(get<0>(this->nodes[current_node].info) > i)
        {
            current_node = this->nodes[current_node].left;
        }
    }
    return NULL_TELEM;
}
//BC = Theta(1) (when the element we're looking for is on the position given, WC = Theta(nr_elements) (when the element's the last in our
// search) => TOTAL = O(log nr_elements), since the search narrows down our options

TElem Matrix::modify(int i, int j, TElem e)
{
    if (i < 0 || i >= this->nr_lines || j < 0 || j >= this->nr_columns)
    {
        throw exception();
    }

    int current_node = this->root;
    int parent = -1;

    // look for the node corresponding to the position (i, j)
    while (current_node != -1)
    {
        parent = current_node;
        if (get<0>(this->nodes[current_node].info) == i && get<1>(this->nodes[current_node].info) == j) // when found
        {
            TElem previousValue = get<2>(this->nodes[current_node].info);
            get<2>(this->nodes[current_node].info) = e;
            return previousValue;
        }
        else if (get<0>(this->nodes[current_node].info) > i || (get<0>(this->nodes[current_node].info) == i && get<1>(this->nodes[current_node].info) > j))
        {
            current_node = this->nodes[current_node].left;
        }
        else
        {
            current_node = this->nodes[current_node].right;
        }
    }

    // if the position (i, j) doesn't exist, create a new node for it

    // no more empty nodes, resize the array:
    if (this->first_empty == -1)
    {
        int new_capacity = capacity * 2;
        Node* new_nodes = new Node[new_capacity];

        // copy existing nodes to the new array
        for (int k = 0; k < capacity; k++) {
            new_nodes[k] = nodes[k];
        }

        // initialize the rest of the new nodes
        for (int k = capacity; k < new_capacity - 1; k++) {
            new_nodes[k].left = k + 1;
            new_nodes[k].right = -1;
            new_nodes[k].parent = -1;
            get<2>(new_nodes[k].info) = NULL_TELEM;
        }

        new_nodes[new_capacity - 1].left = -1;
        new_nodes[new_capacity - 1].right = -1;
        new_nodes[new_capacity - 1].parent = -1;
        get<2>(new_nodes[new_capacity - 1].info) = NULL_TELEM;

        delete[] this->nodes;
        this->nodes = new_nodes;
        this->first_empty = capacity;
        this->capacity = new_capacity;
    }

    // create a new node with the given value
    int new_node = this->first_empty;
    this->first_empty = nodes[first_empty].left;
    this->nodes[new_node].info = std::make_tuple(i, j, e);
    this->nodes[new_node].left = -1;
    this->nodes[new_node].right = -1;
    this->nodes[new_node].parent = parent;

    // update
    if (parent == -1)
    {
        this->root = new_node;
    }
    else if (get<0>(this->nodes[parent].info) > i || (get<0>(this->nodes[parent].info) == i && get<1>(this->nodes[parent].info) > j)) {
        this->nodes[parent].left = new_node;
    }
    else {
        this->nodes[parent].right = new_node;
    }

    this->nr_elements++;
    return NULL_TELEM;
}
//BC = Theta(1) (if no resizing is done and the search is not needed)
//AC = Theta(log nr_elements) (if the search happens, yet no resizing is necessary)
//WC = Theta(nr_elements * log nr_elements) (if both the search happens, and the resizing too)
//=> TOTAL: O(nr_elements * log nr_elements)

void Matrix::setElemsOnLine(int line, TElem elem) {
    if (line < 0 or line >= this->nr_lines)
        throw exception();

    for(int j=0; j<this->nr_columns; j++)
        modify(line, j, elem);
}
// since the modify function is called, we need to be careful of its complexity here
// BC = Theta(1), WC = Theta(nr_columns * nr_elements * log nr_elements) since we modify it nr_columns times
// TOTAL : O(nr_columns * nr_elements * log nr_elements)



