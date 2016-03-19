#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>

#define N 9
#define UNINITIALIZED -1

void randomizeBoard(int * p);
void initialize2DArray(int * p);
void print2DArray(int * p);
bool solveSudoku(int * p);
int findStartingPosition(int * p);
bool isPositionValid(int * p, int val, int col, int row);
bool isBoxValid(int * p, int val, int col, int row);
bool isRowValid(int * p, int val, int col, int row);
bool isColValid(int * p, int val, int col);

int main()
{
	// Game Board
	int myBoard[N][N];

	// Game Board Pointer
	int* myBoardPointer = (int*)myBoard;

	// Initialize Array with Default Values
	initialize2DArray(myBoardPointer);

	randomizeBoard(myBoardPointer);

	std::cout << "Original Board:\n";
	print2DArray(myBoardPointer);

	if (solveSudoku(myBoardPointer))
	{
		std::cout << "Solved: \n";
		print2DArray(myBoardPointer);
	}
	else
	{
		std::cout << "No Solution Exists: \n";
	}
		

	
	

	return 1;
}


void randomizeBoard(int * p)
{

	srand(time(NULL));

	int randomValue = 5;

	int offset;

	for (int col = 0; col < N; col++)
	{
		for (int row = 0; row < N; row++)
		{
			offset = ((row)* 9) + col;
			if ((rand() % 10 + 1) <= 2)
			{
				randomValue = rand() % 9 + 1;
				if (isPositionValid(p, randomValue, col, row))
					*(p + offset) = randomValue;
			}	
		}
	}
}

int findStartingPosition(int * p)
{
	int offset;
	
	for (int i = 0; i < N*N; i++)
	{
		if (*(p + i) == UNINITIALIZED)
		{
			
			return i;
		}
	}
	return -1;
}


bool solveSudoku(int * p)
{
	//print2DArray(p);
	//std::cout << "\n";
	int col, row;

	int offset = findStartingPosition(p);
	if (offset == -1)
		return true;

	row = offset / 9;
	col = offset % 9;

	// Possible Numbers are 1 through 9
	for (int i = 1; i < 10; i++)
	{
		if (isPositionValid(p, i, col, row))
		{
			// Try Possible Value
			*(p + offset) = i;

			// Recursion
			if (solveSudoku(p))
			{
				return true;
			}
			
			// Backtracking if returned false
			*(p + offset) = UNINITIALIZED;
		}
	}
	return false;
}

// Function to Contain Position Validity Checking
bool isPositionValid(int * p, int val, int col, int row)
{
	if (isBoxValid(p, val, col, row) && isRowValid(p, val, col, row) && isColValid(p, val, col))
		return true;

	return false;
}

bool isBoxValid(int * p, int val, int col, int row)
{

	int colOffset = (col - col % 3);
	int rowOffset = (row - row % 3);

	int colEnd = colOffset + 3;
	int rowEnd = rowOffset + 3;

	int offset = 0;

	for (rowOffset; rowOffset < rowEnd; rowOffset++)
	{
		for (colOffset; colOffset < colEnd; colOffset++)
		{
			offset = ((rowOffset ) * 9) + colOffset;

			if (*(p + offset) == val)
			{
				return false;
			}
		}
		colOffset = (col - col % 3);
	}
	return true;
}

bool isColValid(int * p, int val, int col)
{
	// Determine Position in 9x9 2D Array

	for (int i = 0; i < 9; i++)
	{
		if (val == *((p + (col)) + (i * 9)))
			return false;
	}
	return true;
}

// Zero Indexed
bool isRowValid(int * p, int val, int col, int row)
{

	// Determine Position in 9x9 2D Array
	int pos = ((row) * 9) + col;

	// Zero Offset
	pos--;

	// Get Upper and Lower Bounds of Row
	int startRow = ((row) * 9);
	int endRow = ((row) * 9) + 9;

	// If Value is in row return False
	for (int i = startRow; i < endRow; i++)
	{
		//std::cout << *(p + i) << " ";
		if (val == *(p + i))
			return false;
	}
	

	// Else Return True
	return true;
}

void initialize2DArray(int * p)
{
	for (int i = 0; i < N*N; i++)
	{
		//*(p + i) = i + 1;
		*(p + i) = UNINITIALIZED;
	}

}

void print2DArray(int * p)
{
	for (int i = 1; i <= N*N; i++)
	{
		printf("%2d ", *(p + (i - 1)));
		if (i % 9 == 0)
			printf("\n");
	}
}