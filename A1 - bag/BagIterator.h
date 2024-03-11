#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
    int current; // current position of the "numbers" that make up the frequencies
    int current_count_of_element; // iterating through the frequency (ex: for freq 4, this goes 1->4)

	BagIterator(const Bag& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
