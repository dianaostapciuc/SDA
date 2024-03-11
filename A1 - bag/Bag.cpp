#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {

    this->minimum_element = MAX;
    this->maximum_element = MIN;
    this->range = 0;
    this->elements = new TElem[0];
}
//Theta(1)

void Bag::add(TElem elem) {

    if (elem < this->minimum_element or elem >this->maximum_element)
        adding_to_vector(elem);
    this->elements[elem - this->minimum_element]++;

}
//BEST CASE: Theta(1), WORST CASE: Theta(range), TOTAL: O(range)

void Bag::adding_to_vector(TElem elem){
    //TODO - Implementation
    // CASE 1: first element that's added
    // CASE 2: elem < min
    // CASE 3: elem > max
    TElem *new_elements;
    if (this->range == 0)
    {
        new_elements = new TElem [1];
        this->range = 1;
        this->minimum_element = elem;
        this->maximum_element = elem;
        new_elements[0] = 0;
        this->elements = new_elements;
    }
    else if (elem < this->minimum_element)
    {
        int add_positions = this->minimum_element - elem;
        this->range += add_positions;
        new_elements = new TElem [this->range];
        for (int i=0; i<add_positions; i++)
            new_elements[i] = 0;
        for (int i = add_positions; i < this->range; i++)
            new_elements[i] = this->elements[i-add_positions];
        this->elements = new_elements;
        this->minimum_element = elem;
    }
    else if (elem > this->maximum_element)
    {
        int add_positions = elem - this->maximum_element;
        this->range += add_positions;
        new_elements = new TElem [this->range];
        for (int i = 0; i< this->range - add_positions; i++)
            new_elements[i] = this->elements[i];
        for (int i= this->range - add_positions; i< this->range; i++)
            new_elements[i] = 0;
        this->elements = new_elements;
        this->maximum_element = elem;
    }

}
//BEST CASE: Theta(1), WORST CASE: Theta(range), TOTAL COMPLEXITY: O(range)

bool Bag::remove(TElem elem) {

    if (elem >= this->minimum_element and elem <= this->maximum_element)
    {
        if (this->elements[elem - this->minimum_element] != 0)
        {
            this->elements[elem - this->minimum_element]--;
            return true;
        }
    }
    return false;
}
//Theta(1)

bool Bag::search(TElem elem) const
{

    if (elem < this->minimum_element or elem > this->maximum_element)
        return false;
    else if (this->elements[elem - this->minimum_element] != 0)
        return true;
    return false;
}
//Theta(1)

int Bag::nrOccurrences(TElem elem) const {

    if (search(elem))
        return this->elements[elem - this->minimum_element];
    return false;
}
//Theta(1)

int Bag::size() const {

    int current_size = 0;
    for(int i = 0; i<this->range; i++)
        if (this->elements[i] != 0)
            current_size+= this->elements[i];
    return current_size;

}
//BEST CASE: Theta(1), WORST CASE: Theta(range), TOTAL: O(range)

bool Bag::isEmpty() const {

    int ok = 0;
    for (int i = 0; i < this->range; i++)
        if (this->elements[i] != 0)
            ok = 1;
    if (ok == 0)
        return true;
    return false;
}
//Theta(range), TOTAL: O(range)

int Bag::removeElementsWithMultipleOccurrences()
{
    int nr_of_removed_elements = 0;
    for (int i=0; i<this->range; i++)
    {
        if (this->elements[i] != 0 and this->elements[i] != 1)
        {
            nr_of_removed_elements += this->elements[i];
            this->elements[i] = 0;
        }
    }
    return nr_of_removed_elements;
}
//Theta(range), TOTAL: O(range)

BagIterator Bag::iterator() const {
    return BagIterator(*this);
}
//O(range)

Bag::~Bag() {
    delete[] this->elements;
}
//Theta(1)