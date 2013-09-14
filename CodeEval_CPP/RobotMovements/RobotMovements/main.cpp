//
//  main.cpp
//  RobotMovements
//
//  Created by Derrick Ho on 8/26/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include <iostream>

typedef struct _point {
	int x;
	int y;
}Point;

class MatrixNxM {
	Point **matrix;
	int numOfCol;
	int numOfRow;
	void initMatrix();
	void walkMatrix(void(^action)(Point ** refToPointPointer));
public:
	/*creates a MatrixNxM object with specific dimensions*/
	MatrixNxM(int numOfCol, int numOfRow);
	~MatrixNxM();
	MatrixNxM & operator=(const MatrixNxM &rhs);
	/*counds the number of paths to go from (0,0) to (col, row)*/
	int paths();
};

MatrixNxM::MatrixNxM(int numOfCol, int numOfRow) {
	this->numOfCol = numOfCol;
	this->numOfRow = numOfRow;
	this->initMatrix ();
}
MatrixNxM::~MatrixNxM() {
	walkMatrix(^(Point ** p) {
		if (*p) {
			printf("(%d, %d)\n", (*p)->x, (*p)->y);
			delete *p;
		} else {
			printf("(-,-)\n");
		}
	});
	delete [] matrix;
}
MatrixNxM & MatrixNxM::operator=(const MatrixNxM &rhs) {
	if (this != &rhs) {
		//TODO: deallocate, allocate and copy
	}
	return *this;
}
void MatrixNxM::initMatrix() {
	//TODO:allocate a matrix
	int matrixSize = (numOfCol +1) * (numOfRow +1);
	this->matrix = new Point *[matrixSize];
	walkMatrix(^(Point **p){
		*p = NULL;//new Point;
	});
}
void MatrixNxM::walkMatrix(void(^action)(Point **)) {
	for (int i = 0; i < (numOfCol +1) * (numOfRow +1); ++i) {
		action( &(matrix[i]));
	}
}
int MatrixNxM::paths() {
	return 0;
}
int main(int argc, const char * argv[])
{

	// insert code here...
	std::cout << MatrixNxM(2,2).paths() << "\n";
    return 0;
}

