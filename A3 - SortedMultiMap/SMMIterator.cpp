#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->current_key_index = map.head;
    this->current_element_index = map.values[map.head].head;
}
// BC = WC = AC = Theta(1)
void SMMIterator::first(){
	this->current_key_index = map.head;
    this->current_element_index = map.values[map.head].head;
}
// BC = WC = AC = Theta(1)

void SMMIterator::next(){
	if (!valid())
        throw exception();
    if (map.values[this->current_key_index].next[this->current_element_index] != -1)
        this->current_element_index = map.values[this->current_key_index].next[this->current_element_index];
    else
    {
        this->current_key_index = map.next[this->current_key_index];
        this->current_element_index = map.values[this->current_key_index].head;
    }
}
// BC = WC = AC = Theta(1)
bool SMMIterator::valid() const{
	if (this->current_key_index != -1)
        return true;
    return false;
}
// BC = WC = AC = Theta(1)
TElem SMMIterator::getCurrent() const{
    if (!valid())
        throw exception();
    TKey currentKey = map.keys[this->current_key_index];
    TValue currentValue = map.values[this->current_key_index].value[this->current_element_index];
    TElem currentElement;
    currentElement.first = currentKey;
    currentElement.second = currentValue;
    return currentElement;
}
// BC = WC = AC = Theta(1)


