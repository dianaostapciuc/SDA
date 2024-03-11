#include "SMIterator.h"
#include "SortedMap.h"
#include <stdexcept>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m) {
    current = 0; // Initialize the current index to 0
    size = map.length; // Get the length of the map and assign it to size
    elements = new TElem[size]; // Create a dynamic array of TElem to store the elements
    buildSortedArray(); // Build a sorted array of elements from the map
}
// BC = WC = AC = Theta(1)

void SMIterator::buildSortedArray() {
    int count = 0; // Initialize a count variable to keep track of the number of elements

    // Iterate through the hash table of the map
    for (const auto& list : map.hashTable) {
        for (const auto& elem : list) {
            elements[count] = elem; // Store each element in the array
            count++; // Increment the count
        }
    }

    // Sort the elements array using bubble sort algorithm
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (!map.rel(elements[j].first, elements[j + 1].first)) {
                // swap the elements
                TElem temp = elements[j];
                elements[j] = elements[j + 1];
                elements[j + 1] = temp;
            }
        }
    }
}
//BEST CASE: Theta(1), WORST CASE: Theta(count^2), TOTAL: O(count^2)

void SMIterator::first()
{
    current = 0; // Set the current index to the beginning of the array
}
// BC = WC = AC = Theta(1)

void SMIterator::next() {
    if (!valid()) {
        throw std::exception(); // Throw an exception if the iterator is not valid
    }
    current++; // Move to the next index
}
// BC = WC = AC = Theta(1)

bool SMIterator::valid() const {
    return current < size; // Check if the current index is within the range of the array size
}
// BC = WC = AC = Theta(1)

TElem SMIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception(); // Throw an exception if the iterator is not valid
    }
    return elements[current]; // Return the element at the current index
}
// BC = WC = AC = Theta(1)

void SMIterator::jumpForward(int k)
{
    if (k < 0)
        throw std::exception();
    if (k + current > size)
        throw std::exception();
    while (k > 0)
    {
        next();
        k--;
    }
}

// BC = Theta(1) (when k is 1), WC = Theta(k), AC = O(k)
