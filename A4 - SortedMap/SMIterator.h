#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
    const SortedMap& map;
    int current;
    int size;
    TElem* elements;

    SMIterator(const SortedMap& mapionar);

    // Helper functions
    void buildSortedArray();

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
    void jumpForward(int k);
};

