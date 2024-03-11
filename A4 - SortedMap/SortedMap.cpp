#include "SMIterator.h"
#include "SortedMap.h"
#include <stdexcept>
using namespace std;

SortedMap::SortedMap(Relation r) {
    this->rel = r; // Initialize the relation
    this->capacity = 10; // Initialize the capacity of the hash table
    this->length = 0; // Initialize the length (number of elements)
    this->hashTable = std::vector<std::list<TElem>>(this->capacity); // Create the hash table with initial capacity
}

TValue SortedMap::add(TKey k, TValue v) {
    int index = abs(k % this->capacity); // Compute the index in the hash table based on the key
    for (auto& elem : this->hashTable[index]) { // Iterate through the elements at the computed index
        if (elem.first == k) { // If the key already exists in the hash table
            TValue oldValue = elem.second; // Store the old value
            elem.second = v; // Update the value with the new value
            return oldValue; // Return the old value
        }
    }
    this->hashTable[index].push_back(std::make_pair(k, v)); // Add a new key-value pair at the computed index
    this->length++; // Increase the length
    if (this->length > this->capacity) { // If the length exceeds the capacity
        this->capacity *= 2; // Double the capacity
        std::vector<std::list<TElem>> newHashTable(this->capacity); // Create a new hash table with the updated capacity
        for (auto& list : this->hashTable) { // Iterate through the old hash table
            for (auto& elem : list) { // Iterate through the elements in each list
                int newIndex = abs(elem.first % this->capacity); // Recompute the index for the element based on the new capacity
                newHashTable[newIndex].push_back(elem); // Add the element to the new hash table at the updated index
            }
        }
        this->hashTable = newHashTable; // Update the hash table with the new hash table
    }
    return NULL_TVALUE; // Return the null value indicating the key did not exist before
}
//BEST CASE: Theta(1) (when we add on the first position), WORST CASE: Theta(length) (when random), TOTAL: O(length)

TValue SortedMap::search(TKey k) const {
    int index = abs(k % this->capacity); // Compute the index in the hash table based on the key
    for (auto& elem : this->hashTable[index]) { // Iterate through the elements at the computed index
        if (elem.first == k) { // If the key is found
            return elem.second; // Return the corresponding value
        }
    }
    return NULL_TVALUE; // Return the null value indicating the key was not found
}
//BEST CASE: Theta(1) (when we search for the first element), WORST CASE: Theta(length) (when random), TOTAL: O(length)

TValue SortedMap::remove(TKey k) {
    int index = abs(k % this->capacity); // Compute the index in the hash table based on the key
    for (auto it = this->hashTable[index].begin(); it != this->hashTable[index].end(); it++) { // Iterate through the elements at the computed index
        if (it->first == k) { // If the key is found
            TValue value = it->second; // Store the corresponding value
            this->hashTable[index].erase(it); // Remove the element from the hash table
            this->length--; // Decrease the length
            return value; // Return the removed value
        }
    }
    return NULL_TVALUE; // Return the null value indicating the key was not found
}
//BEST CASE: Theta(1) (when we delete the first element), WORST CASE: Theta(length) (when random), TOTAL: O(length)

int SortedMap::size() const {
    return length;
}
// BC = WC = AC = Theta(1)

bool SortedMap::isEmpty() const {
    return length==0;
}
// BC = WC = AC = Theta(1)

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
    hashTable.clear();
    capacity = 0;
    length = 0;
}
