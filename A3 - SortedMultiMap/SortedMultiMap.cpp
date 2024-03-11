#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    this->r = r;
    this->capacity = 10;
    this->keys = new TKey[capacity];
    this->values = new SLLA[capacity];
    this->next = new int[capacity];
    this->head = -1;
    this->key_length = 0;
    this->first_free = 0;
    this->total_length = 0;

    for (int i = 0; i < this->capacity; i++)
    {
        next[i] = -1;
        keys[i] = NULL_TVALUE;
    }
}
//BEST CASE: Theta(capacity), WORST CASE: Theta(capacity), TOTAL: O(capacity)

void SortedMultiMap::resize()
{
    capacity *= 2;
    TKey* newKeys = new TKey[capacity];
    SLLA* newValues = new SLLA[capacity];
    int* newNext = new int[capacity];
    for (int i = 0; i < this->key_length; i++)
    {
        newKeys[i] = keys[i];
        for (int j = 0; j < values[i].length; j++) {
            newValues[i].value[j] = values[i].value[j];
            newValues[i].next[j] = values[i].next[j];
        }
        newValues[i].first_free = values[i].first_free;
        newValues[i].head = values[i].head;
        newValues[i].length = values[i].length;
        newNext[i] = next[i];
    }
    for (int i = this->key_length; i < capacity; i++) {
        newNext[i] = -1;
        newKeys[i] = NULL_TVALUE;
    }
    delete[] keys;
    delete[] values;
    delete[] next;
    keys = newKeys;
    values = newValues;
    next = newNext;
    first_free = key_length;
}
//BEST CASE: Theta(capacity), WORST CASE: Theta(capacity), TOTAL: O(capacity)

void SortedMultiMap::add(TKey c, TValue v) {
    if (this->key_length == capacity)
        resize();
    if (head == -1 || !r(keys[head], c)) //if we add on the first position
    {
        keys[this->first_free] = c; //adding the key on the first empty place
        values[this->first_free].value[values[this->first_free].first_free] = v; // adding the value on each key's slla where possible
        values[this->first_free].length++;
        values[this->first_free].head = values[this->first_free].first_free; // updating the head
        values[this->first_free].first_free++; // updating first free position
        next[this->first_free] = head; // next position points to what the head pointed to
        head = first_free;
        key_length++;
        total_length++;
        for (int i = 0; i <= key_length; i++) // finding the first_free for the key
            if (keys[i] == NULL_TVALUE){
                first_free = i;
                break;
            }

    }
    //random position on the slla
    else
    {
        int current = head;
        while (next[current] != -1 && r(keys[next[current]], c))
            current = next[current]; // getting the position where we have to add

        if (keys[current] == c) // if the key already exists
        {
            if (values[current].length == values[current].capacity)
                values[current].resize();

            values[current].value[values[current].first_free] = v; // adding the value
            values[current].length++;
            total_length++; // increasing the values
            int currentValue = values[current].head;
            while (values[current].next[currentValue] != -1)
                currentValue = values[current].next[currentValue];
            values[current].next[currentValue] = values[current].first_free;
            for (int i = 0; i <= values[current].length; i++) // finding the next first_free
                if (values[current].value[i] == NULL_TVALUE) {
                    values[current].first_free = i;
                    break;
                }
        }
        else // if the key doesn't exist and we have to add it too
        {
            keys[this->first_free] = c; // adding the key as well
            values[this->first_free].value[values[this->first_free].first_free] = v;
            values[this->first_free].length++;
            values[this->first_free].head = values[this->first_free].first_free;
            values[this->first_free].first_free++;
            next[this->first_free] = next[current];
            next[current] = first_free;
            key_length++;
            total_length++;
            for (int i = 0; i <= key_length; i++) // finding the first_free for the keys
                if (keys[i] == NULL_TVALUE) {
                    first_free = i;
                    break;
                }
        }
    }
}
//BEST CASE: Theta(1) (if we add on the first position), WORST CASE: Theta(length) (when the position's random)
//TOTAL: O(length)

vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> result;
    int current = head;
    while (current != -1)
    {
        if (keys[current] == c)
        {
            for (int i = 0; i < values[current].length; i++)
            {
                result.push_back(values[current].value[i]);
            }
            break;
        }
        current = next[current];
    }
    return result;
}
//BEST CASE: Theta(1) (if we search for first element), WORST CASE: Theta(length) (when the element's random)
//TOTAL: O(length)

bool SortedMultiMap::remove(TKey c, TValue v) {
    int current = head;
    int previous = -1;
    while (current != -1 && keys[current] != c) {
        previous = current;
        current = next[current];
    } // searching for the key to be removed

    if (current == -1)
        return false; // false if it doesnt exist

    // search for value in the current list
    int valueIndex = -1;
    for (int i = values[current].head; i != -1; i = values[current].next[i])
        if (values[current].value[i] == v) {
            valueIndex = i;
            break;
        }

    if (valueIndex == -1) // false if it doesn't exist
        return false;

    // remove value from the list
    if (values[current].head == valueIndex)
    {
        values[current].head = values[current].next[valueIndex];
    } // if its the head
    else // if random
    {
        values[current].next[previous] = values[current].next[valueIndex];
    }
    values[current].value[valueIndex] = NULL_TVALUE;
    values[current].next[valueIndex] = -1;
    values[current].first_free = valueIndex;
    values[current].length--;
    total_length--;

    if (values[current].length == 0) {
        // remove key from the map if the list of values is empty
        if (current == head) {
            head = next[current];
        } else {
            next[previous] = next[current];
        }
        keys[current] = NULL_TVALUE;
        next[current] = first_free;
        first_free = current;
        key_length--;
    }

    return true;
}
//BEST CASE: Theta(1) (when we remove the first element), WORST: Theta(length) (when we remove a random one)
//TOTAL: O(length)


int SortedMultiMap::size() const {
	return total_length;
}
//BC = WC = AC = Theta(1)

bool SortedMultiMap::isEmpty() const {
	if (key_length == 0)
        return true;
    return false;
}
//BC = WC = AC = Theta(1)

int SortedMultiMap::addIfNotPresent(SortedMultiMap& smm)
{
    int addedPairs = 0;
    for (int i = 0; i < smm.key_length; i++) // iterate through the keys
    {
        TKey currentKey = smm.keys[i];
        bool keyExists = false;
        for (int j = 0; j < key_length; j++)
        {
            if (keys[j] == currentKey)
            {
                keyExists = true; // if we find one that exists, we break and we dont add its values
                break;
            }
        }
        if (!keyExists)
        {
            vector<TValue> searchResult = smm.search(currentKey);
            for (const auto& value : searchResult)
            {
                add(currentKey, value);
                addedPairs++;
            }
        }
    }
    return addedPairs;
}
//BC = WC = AC = O(smm.key_length * key_length)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	delete[] keys;
    delete[] values;
    delete[] next;
}
