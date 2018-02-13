#include "main.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

//Fill a 2D array matrix with random values
void fillMatrix(int matrix[rows][cols])
{
	/* initialize random seed: */
	srand(time(NULL));

	//For each row, go to each go to each entry by sweeping columns
	for (int row = 0; row < rows; row++) 
	{
		for (int col = 0; col < cols; col++)
		{
			/* generate number between 1 and 10 for the matrix's entries */
			matrix[row][col] = rand() % 10 + 1;
		}
	}

}

//Fill a 2D array matrix with constant
void fillMatrix(int matrix[rows][cols], int constant)
{
	/* initialize random seed: */
	srand(time(NULL));

	//For each row, go to each go to each entry by sweeping columns
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			/* generate number between 1 and 10 for the matrix's entries */
			matrix[row][col] = constant;
		}
	}

}

//Fill a 2D array matrix with random values using pointer. Matrix dimensions passed by reference
void fillMatrixPtr(int (*ptr_matrix)[rows][cols], int &rows, int &cols)
{
	/* initialize random seed: */
	srand(time(NULL));

	//For each row, go to each go to each entry by sweeping columns
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			/* generate number between 1 and 10: */
			(*ptr_matrix)[col][row] = rand() % 10 + 1;
		}
	}

}

//Fill a 2D array matrix with a constant for all entries using pointer. Matrix dimensions passed by reference.
void fillMatrixPtr(int (*ptr_matrix)[rows][cols], int &rows, int &cols, int constant)
{
	/* initialize random seed: */
	srand(time(NULL));

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			/* generate number between 1 and 10: */
			(*ptr_matrix)[col][row] = constant;
		}
	}

}

//Fill a 2D array matrix with random values using pointer. 
void fillMatrixPtr1D(int(*ptr_matrix)[rows*cols], int &rows, int &cols)
{
	/* initialize random seed: */
	srand(time(NULL));

	//For each row, go to each go to each entry by sweeping columns
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			/* generate number between 1 and 10: */
			(*ptr_matrix)[cols*row+col] = rand() % 10 + 1;
		}
	}

}

//Print 1D Array matrix
void printMatrix1DArray(int array[], int &size, int &cols) 
{
	//Sweep through all values
	for (int i = 0; i < size; i++) 
	{	
		//If current index is a multiple of cols, 
		//this element is the first value of a row.
		//So skip line to start printing new row.
		if (i%cols == 0)
		{
			cout << endl;
		}
		cout << array[i] << ' ';
	}
	cout << endl;
}

//Print a 2D Array matrix
void printMatrix(int matrix[rows][cols])
{
	for (int row = 0; row < rows; row++)
	{
		cout << "row " << row << ": ";
		for (int col = 0; col < cols; col++)
		{
			cout << matrix[row][col] << " ";
		}
		cout << endl;
	}
}

//Print a 2D Array matrix using pointers
void printMatrixPtr(int (*matrix)[rows][cols], int &rows, int &cols)
{
	for (int row = 0; row < rows; row++)
	{
		cout << "row " << row << ": ";
		for (int col = 0; col < cols; col++)
		{
			cout << (*matrix)[row][col] << " ";
		}
		cout << endl;
	}
}

//Swap 2 elements of a 2D Array matrix
void swapMatrixElements(int matrix[rows][cols], int &row, int &col)
{
	int temp;
	temp = matrix[row][col];
	matrix[row][col] = matrix[col][row];
	matrix[col][row] = temp;
}

//Swap 2 elements of a 2D array matrix using pointers
void swapMatrixElementsPtr(int (*matrix)[rows][cols], int &row, int &col)
{
	int temp;
	temp = (*matrix)[row][col];
	(*matrix)[row][col] = (*matrix)[col][row];
	(*matrix)[col][row] = temp;
}

//Transpose a 2D Array Matrix
void transposeMatrix(int matrix[rows][cols])
{	
	//Sweep through rows
	for (int row = 0; row < rows - 1; row++)
	{	
		//For each row, only go through the entry in the upper triangular matrix
		//and swap them with their corresponding entry in the lower triangular matrix
		//Example:
		//Take this 3x3 matrix
		//a11 a12 a13
		//a21 a22 a23
		//a31 a32 a33
		//Here a12 is in the upper triangular matrix and its corresponding entry in the lower triangular matrix is a21
		//Same relation for the pairs a13-a31 and a23-a32
		int col_start_index = row + 1;

		for (int col = col_start_index; col < cols; col++)
		{
			swapMatrixElements(matrix, row, col);
		}
	}
}

//Transpose a 2D Array Matrix using pointers. (See function above for in depth explanation of algorithm)
void transposeMatrix(int (*matrix_ptr)[rows][cols], int &rows, int &cols)
{
	for (int row = 0; row < rows - 1; row++)
	{
		int col_start_index = row + 1;

		for (int col = col_start_index; col < cols; col++)
		{
			swapMatrixElementsPtr(matrix_ptr, row, col);
		}
	}
}

//Multiply matrixA and matrixB and put result in matrixC
//This algorithm is the long method with O(n^3) complexity
int multMatrices(int matrixA[rows][cols], int matrixB[rows][cols], int result[rows][cols])
{	
	//Sweep rows of A
	for(int rowA = 0; rowA < rows; rowA++)

		//For each rows of A, sweep cols of B
		for (int colB = 0; colB < cols ; colB++)
		{	
			int sum = 0;

			//For each cols of B, sweep the rows of B and the cols of A  and multiply the corresponding entries
			for (int colA_rowB = 0; colA_rowB < cols; colA_rowB++)
			{
				sum += matrixA[rowA][colA_rowB] * matrixB[colA_rowB][colB];
			}
			result[rowA][colB] = sum;
		}
	return 0;
}


//Multiply matrixA with matrixB and put the result in matrixC
//This algorithm uses recursion and is faster than the long method with O(n^2) complexity
void matrixMultrecursive(int matrixA[rows][cols], int matrixB[rows][cols], int matrixC[rows][cols], int rowSizeA, int colSizeA, int rowSizeB, int colSizeB)
{
	static int i = 0, j = 0, k = 0;

	// If all rows sweeped.
	if (i >= rowSizeA)
		return;

	//Executed colSizeB + 1 times
	// If i < rowSizeA
	if (j < colSizeB)
	{
		if (k < colSizeA)
		{
			matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			k++;

			matrixMultrecursive(matrixA, matrixB, matrixC, rowSizeA, colSizeA, rowSizeB, colSizeB);
		}

		k = 0;
		j++;
		matrixMultrecursive(matrixA, matrixB, matrixC, rowSizeA, colSizeA, rowSizeB, colSizeB);
	}

	//Executed rowSizeA times
	j = 0;
	i++;
	matrixMultrecursive(matrixA, matrixB, matrixC, rowSizeA, colSizeA, rowSizeB, colSizeB);
}



int main()
{

	int matrixA_2D_array[rows][cols];
	int matrixB_2D_array[rows][cols];
	int matrixC_2D_array[rows][cols];
	int matrixC_recursive_2D_array[rows][cols];

	//Question #2
	cout << "####--Intro to C++ - Assignment 1---####" << endl << endl;
	fillMatrix(matrixA_2D_array);
	fillMatrix(matrixB_2D_array);
	
	//Question #3
	cout << "-----------Question 3-------" << endl << endl;
	cout << "Matrix A Initialized To:" << endl;
	printMatrix(matrixA_2D_array);
	cout << "----------------------" << endl << endl;

	//Question #4
	cout << "-----------Question 4-------" << endl << endl;
	transposeMatrix(matrixA_2D_array);
	cout << "Matrix A After Simple Transpose Operation" << endl;
	printMatrix(matrixA_2D_array);
	cout << "----------------------" << endl << endl;


	//Question #5
	cout << "-----------Question 5-------" << endl << endl;

	
	//Initialize matrices with constant 2 for each entry of A and B and constant 0 for C
	//**MESSAGE TO GRADER: You can remove the constant 2 passed as arguments in the fillMatrix function
	//to fill matrices A and B with random numbers. Though, matrix C must be reinitialized with 0 or a new variable
	//must be used in order to have a correct output
	fillMatrix(matrixA_2D_array, 2);
	fillMatrix(matrixB_2D_array, 2);
	fillMatrix(matrixC_2D_array, 0);
	cout << "Multiplying Matrix A:" << endl;
	printMatrix(matrixA_2D_array);
	cout << "With Matrix B" << endl;
	printMatrix(matrixB_2D_array);

	//Multiply matrices using long method
	multMatrices(matrixA_2D_array, matrixB_2D_array, matrixC_2D_array);
	cout << "Long Method Matrix Mutliplication (A * B) Result:" << endl;

	//Print result of operation
	printMatrix(matrixC_2D_array);
	cout << "----------------------" << endl << endl;

	//Question #6 
	cout << "-----------Question 6-------" << endl << endl;
	
	//Reinitialize matrices A, B and C
	fillMatrix(matrixA_2D_array, 2);
	fillMatrix(matrixB_2D_array, 2);
	fillMatrix(matrixC_2D_array, 0);

	cout << " Multiplying Matrix A:" << endl;
	printMatrix(matrixA_2D_array);
	cout << "With Matrix B:" << endl;
	printMatrix(matrixB_2D_array);

	cout << endl;
	cout << "Reinitiliazed Result Matrix C to:" << endl;
	printMatrix(matrixC_2D_array);

	//Multiply matrices using recursive algorithm
	matrixMultrecursive(matrixA_2D_array, matrixB_2D_array, matrixC_2D_array, 5, 5, 5, 5);
	cout << "Recursive Matrix Mutliplication (A * B) Result:" << endl;

	//Print result of operation
	printMatrix(matrixC_2D_array);
	cout << "----------------------" << endl << endl;



	//Question #7
	cout << "-----------Question 7-------" << endl << endl;

	//Initialize new matrix A
	int matrixA[rows][cols];

	//Initializing pointer to Matrix A
	int (*matrixA_ptr)[rows][cols];
	matrixA_ptr = &matrixA;

	//Using new value instead of "const rows" and "const cols" because cannot use const as input for fillMatrixPtr
	int rows_n_cols = 5;

	//Fill Matrix Using Pointers
	fillMatrixPtr(matrixA_ptr, rows_n_cols, rows_n_cols);
	cout << "Matrix Before Transpose Operation" << endl;

	//Print Matrix Using Pointers
	printMatrixPtr(matrixA_ptr, rows_n_cols, rows_n_cols);

	//Transpose Matrix Using Pointers
	transposeMatrix(matrixA_ptr, rows_n_cols, rows_n_cols);

	//Print result of operation
	cout << "Matrix After Transpose Operation" << endl;
	printMatrixPtr(matrixA_ptr, rows_n_cols, rows_n_cols);
	cout << "----------------------" << endl << endl;


	//Question #8
	cout << "-----------Question 8-------" << endl << endl;
	int matrixA1D[rows*cols];

	//Initialize pointer to array
	int(*matrixA1D_ptr)[rows*cols];
	matrixA1D_ptr = &matrixA1D;

	//Fill 5X5 matrix using 1D array
	fillMatrixPtr1D(matrixA1D_ptr, rows_n_cols, rows_n_cols);

	cout << endl;
	cout << "1D Matrix Array size :" << matrix1D_Size << endl;
	cout << "Matrix size (row X col) :" << matrix1D_Size / cols << "X" << cols << endl;

	//Print 5X5 matrix implemented on a 1D array
	printMatrix1DArray(matrixA1D, matrix1D_Size, rows_n_cols);
	cout << "----------------------" << endl << endl;

	return 0;
}

