//
//  main.m
//  11_largestProductInGrid
//
//  Created by Derrick Ho on 8/3/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

int productOfGeneric4(int *grid, CGSize box, CGPoint origin, int(^toolBlock)(int x, int dx, int y, int dy, int width)){
	const int numberToMultiply = 4;
	int n[numberToMultiply];
	int total = 1;
	for (int offset = 0; offset < numberToMultiply; ++offset){
		n[offset] = grid[toolBlock(origin.x, offset, origin.y, offset, box.width)];
		total *= n[offset];
	}
	return total;
}

int productOfHorizontal4(int *grid, CGSize box, CGPoint origin){
	return productOfGeneric4(grid, box, origin, ^int(int x, int dx, int y, int dy, int width) {
		return (x +dx + y*width);
	});
}
int productOfVertical4(int *grid, CGSize box, CGPoint origin){
	return productOfGeneric4(grid, box, origin, ^int(int x, int dx, int y, int dy, int width) {
		return (x + (y+dy)*width);
	});
}
int productOfDiagonalULBR4(int *grid, CGSize box, CGPoint origin){
	return productOfGeneric4(grid, box, origin, ^int(int x, int dx, int y, int dy, int width) {
		return (x +dx + (y +dy)*width);
	});
}
int productOfDiagonalBLUR4(int *grid, CGSize box, CGPoint origin){
	return productOfGeneric4(grid, box, origin, ^int(int x, int dx, int y, int dy, int width) {
		return (x +dx + (y-dy)*width);
	});
}

int largestProductWithinBounds4(int *grid, CGSize box, CGRect bounds, int(*tool)(int *_grid, CGSize _box, CGPoint _origin)){
	int largest = 0;
	for (int y = bounds.origin.y; y < bounds.origin.y + bounds.size.height; ++y) {
		for (int x = bounds.origin.x; x < bounds.origin.x + bounds.size.width; ++x) {
			int product = tool(grid, box,CGPointMake(x, y));
			largest = (largest < product)? product: largest;
		}
	}
	return largest;
}
int main(int argc, const char * argv[])
{
	FILE *f = fopen(argv[1], "r");
	char c[1024];
	if (!f) {
		fprintf(stderr, "Can't open");
		return -1;
	}
	int grid[20*20];
	while (1 == fscanf(f, "%s", c)) {
		static int i = 0;
		grid[i] = (int)strtol(c , NULL, 10);
		++i;
	}

	printf("max horizontal %d\n", largestProductWithinBounds4(grid,
															CGSizeMake(20, 20),
															CGRectMake(0, 0, 17, 20),
															productOfHorizontal4));
	printf("max vertical %d\n", largestProductWithinBounds4(grid,
														  CGSizeMake(20, 20),
														  CGRectMake(0, 0, 20, 17),
														  productOfVertical4));
	printf("max ULBR %d\n", largestProductWithinBounds4(grid,
													  CGSizeMake(20, 20),
													  CGRectMake(0, 0, 17, 17),
													  productOfDiagonalULBR4));
	printf("max BLUR %d\n", largestProductWithinBounds4(grid,
													  CGSizeMake(20, 20),
													  CGRectMake(0, 3, 17, 17),
													  productOfDiagonalBLUR4));
	return 0;
}

