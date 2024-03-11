#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

#include <tuple>
typedef std::tuple <int, int, TElem> MCell;

struct Node{
    MCell info;
    int left;
    int right;
    int parent;
};

class Matrix {

private:
	Node* nodes;
    int root;
    int first_empty;
    int nr_columns;
    int nr_lines;
    int capacity;
    int nr_elements;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    void setElemsOnLine(int line, TElem elem);

};
