#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>
using namespace std;
ListIterator::ListIterator(const IndexedList& list) : list(list){
   this->current_node = list.head;
}
//worst = best = Theta(1)
void ListIterator::first(){
    this->current_node = list.head;
}
//Theta(1)
void ListIterator::next(){
    if (!valid())
        throw exception();
    this->current_node = this->current_node->next;
}
//Theta(1)
bool ListIterator::valid() const{
    return this->current_node != nullptr;
}
//Theta(1)
TElem ListIterator::getCurrent() const{
   if (!valid())
       throw exception();
   return this->current_node->info;
}
//Theta(1)