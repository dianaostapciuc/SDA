#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = 0;
    this->current_count_of_element = 1;
    while (this->bag.elements[this->current] == 0 and this->current <= this->bag.range)
        this->current++;
}
//if the frequency is zero, we cannot iterate an elem that doesn't exist;
//so, as long as in our initial array the freq is zero, we ++ the current position
//until we reach an existent frequency (therefore, the elem exists, so it can be iterated)

//we also have to check to stay within bounds! (range = sum of freq)

//BEST CASE: Theta(1), WORST CASE: Theta(range), TOTAL: O(range)

void BagIterator::first() {
	this->current = 0;
    this->current_count_of_element = 1;
    while (this->bag.elements[this->current] == 0 and this->current <= this->bag.range)
        this->current++;
}
//BEST CASE: Theta(1), WORST CASE: Theta(range), TOTAL: O(range)

void BagIterator::next() {

    if (this->current >= this->bag.range)
    {
        throw exception();
    }
    else
    {
        this->current_count_of_element++;
        if (this->current_count_of_element > this->bag.elements[this->current])
        {
            this->current_count_of_element = 1;
            this->current++;
            while(this->bag.elements[this->current] == 0 and this->current <= this->bag.range)
                this->current++;
        }
    }
}
//current_count_of_element iterates through each value of the freq
//if it is higher than the actual freq, we have to reset it
//then, we use the "while" to locate the next existing freq

//BEST CASE: Theta(1), WORST CASE:Theta(range), TOTAL: O(range)


bool BagIterator::valid() const {

    if (this->current < this->bag.range)
        return true;
	return false;
}
//Theta(1)

TElem BagIterator::getCurrent() const
{
    if (this->current >= this->bag.range || this->bag.range == 0)
    {
        throw exception();
    }
    else return this->bag.minimum_element+current;
}
// to get the actual element for which the frequency is held:
// we add the minimum value that we have with the current position of the existent frequency
// ex: if min = 2, and current = 5, the element that we're looking for is 7 (since 2 is on position 0)

//Theta(1)
