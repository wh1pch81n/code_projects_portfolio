//
//  main.m
//  robotMovements
//
//  Created by Derrick Ho on 9/13/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <stdio.h>

const unsigned int kRow = 4;
const unsigned int kCol = 4;

void printMatrix(int m[kCol][kRow])   {
	int i,j;
	for(i = 0; i < kRow; ++i) {
        for(j = 0; j< kCol; ++j){
			printf("%d, ", m[ j][ i]);
        }
		printf("\n");
    }
	printf("---------------------\n");
}

void robotMovements(int x, int y, int m[kCol][kRow], int *numPathByRef) {
    if(x < 0 || x >= kCol) return;
    if(y < 0 || y >= kRow) return;
	if((x == kCol-1) && (y == kRow-1)){
		*numPathByRef +=1;
		return;
	}
	if(m[x][y]) {
		return;
	}
	m[x][y] = 1;
    robotMovements(x+1,y,m,numPathByRef);
    robotMovements(x-1,y,m,numPathByRef);
    robotMovements(x,y+1,m,numPathByRef);
    robotMovements(x,y-1,m,numPathByRef);
    m[x][y] = 0;
}

int main(int argc, char **argv) {
    int m[kCol][kRow];
    int i,j;
    for(i = 0; i < kCol; ++i) {
        for(j = 0; j< kRow; ++j){
			m[i][j] = 0;
        }
    }
    int numPath = 0;
    robotMovements(0,0,m,&numPath);
    printf("%d\n",numPath);
}