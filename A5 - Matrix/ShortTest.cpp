#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);

    Matrix m2(4,4);
    m2.modify(1,0,1);
    m2.modify(1,1,2);
    m2.modify(1,2,3);
    m2.setElemsOnLine(1,10);
    assert(m2.element(1,0) == 10);
    assert(m2.element(1,1) == 10);
    assert(m2.element(1,2) == 10);
    assert(m2.element(1,3) == 10);

}