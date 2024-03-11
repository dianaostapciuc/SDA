#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
	friend class SMMIterator;
    private:
        struct SLLA
        {
            int capacity;
            int head;
            int *next;
            TValue *value;
            int first_free;
            int length;
            SLLA()
            {
                capacity = 100;
                head = -1;
                next = new int[capacity]();
                value = new TValue[capacity]();
                first_free = 0;
                length = 0;
                for (int i=0; i<capacity; i++)
                {
                    next[i] = -1;
                    value[i] = NULL_TVALUE;
                }
            }
            void resize()
            {
                int newCapacity = capacity * 2;
                int* newNext = new int[newCapacity];
                TValue* newValue = new TValue[newCapacity];

                for (int i = 0; i < capacity; i++)
                {
                    newNext[i] = next[i];
                    newValue[i] = value[i];
                }

                delete[] next;
                delete[] value;

                capacity *= 2;
                next = newNext;
                value = newValue;
                capacity = newCapacity;
            }
            //BEST CASE: Theta(capacity), WORST CASE: Theta(capacity), TOTAL: O(capacity)
            ~SLLA()
            {
                delete[] next;
                delete[] value;
            }
        };
        Relation r;
        int first_free;
        int capacity;
        TKey* keys;
        SLLA* values;
        int* next;
        int head;
        int key_length;
        int total_length;

    public:

    // constructor
    SortedMultiMap(Relation r);

    void resize(); // resizes the SLLA

    int addIfNotPresent(SortedMultiMap& smm);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
