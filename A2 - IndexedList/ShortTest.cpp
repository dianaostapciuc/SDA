#include <assert.h>
#include <exception>

#include "ShortTest.h"
#include "IndexedList.h"
#include "ListIterator.h"




void testAll() {
    IndexedList list = IndexedList();
    assert(list.isEmpty());
    list.addToEnd(1);
    assert(list.size() == 1);
    list.addToPosition(0,2);
    assert(list.size() == 2);
    ListIterator it = list.iterator();
    assert(it.valid());
    it.next();
    assert(it.getCurrent() == 1);
    it.first();
    assert(it.getCurrent() == 2);
    assert(list.search(1) == 1);
    assert(list.setElement(1,3) == 1);
    assert(list.getElement(1) == 3);
    assert(list.remove(0) == 2);
    assert(list.size() == 1);

    list.addToEnd(5);
    list.addToEnd(6);
    list.addToEnd(5);
    list.addToEnd(10);
    list.addToEnd(7);
    list.addToEnd(5);
    list.addToEnd(2);
    list.addToEnd(7);
    assert(list.lastIndexOf(5) == 6);
    assert(list.lastIndexOf(2) == 7);
    assert(list.lastIndexOf(7) == 8);
    assert(list.lastIndexOf(100) == -1);
}
