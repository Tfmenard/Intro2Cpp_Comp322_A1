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

	for (int i = 0; i < size; i++) 
	{
		if (i%cols == 0)
		{
			cout << endl;
		}
		cout << array[i] << ' ';
	}
	cout << endl;
}

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


void swapMatrixElements(int matrix[rows][cols], int &row, int &col)
{
	int temp;
	temp = matrix[row][col];
	matrix[row][col] = matrix[col][row];
	matrix[col][row] = temp;
}

void swapMatrixElementsPtr(int (*matrix)[rows][cols], int &row, int &col)
{
	int temp;
	temp = (*matrix)[row][col];
	(*matrix)[row][col] = (*matrix)[col][row];
	(*matrix)[col][row] = temp;
}

void transposeMatrix(int matrix[rows][cols])
{
	for (int row = 0; row < rows - 1; row++)
	{	
		int col_start_index = row + 1;

		for (int col = col_start_index; col < cols; col++)
		{
			swapMatrixElements(matrix, row, col);
		}
	}
}

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

//A*B
//O(n^2) complexity
int multMatrices(int matrixA[rows][cols], int matrixB[rows][cols], int result[rows][cols])
{
	for(int rowA = 0; rowA < rows; rowA++)

		for (int colB = 0; colB < cols ; colB++)
		{	
			int sum = 0;
			for (int colA_rowB = 0; colA_rowB < cols; colA_rowB++)
			{
				sum += matrixA[rowA][colA_rowB] * matrixB[colA_rowB][colB];
			}
			result[rowA][colB] = sum;
		}
	return 0;
}

//A*B
//O(n^2) complexity
void matrixMultrecursive(
	int row1, int col1, 
	int A[rows][cols], 
	int row2, int col2, 
	int B[rows][cols], 
	int C[rows][cols])
{
	static int i = 0, j = 0, k = 0;

	// If all rows traversed.
	if (i >= row1)
		return;

	//Excecuted m + 1 times
	// If i < row1
	if (j < col2)
	{
		if (k < col1)
		{
			C[i][j] += A[i][k] * B[k][j];
			k++;

			matrixMultrecursive(row1, col1, A, row2, col2, B, C); 
		}

		k = 0;
		j++;
		matrixMultrecursive(row1, col1, A, row2, col2, B, C);
	}

	//Executed n times
	j = 0;
	i++;
	matrixMultrecursive(row1, col1, A, row2, col2, B, C);
}

//A*B
//O(n^2) complexity
void matrixMultrecursive(int matrixA[rows][cols], int matrixB[rows][cols], int matrixC[rows][cols], int rowSizeA, int colSizeA, int rowSizeB, int colSizeB)
{
	static int i = 0, j = 0, k = 0;

	// If all rows traversed.
	if (i >= rowSizeA)
		return;

	//Excecuted m + 1 times
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

	//Executed n times
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
	cout << "-----------Question 2-------" << endl << endl;
	fillMatrix(matrixA_2D_array);
	fillMatrix(matrixB_2D_array);
	cout << "----------------------" << endl << endl;
	
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

	fillMatrix(matrixA_2D_array, 2);
	fillMatrix(matrixB_2D_array, 2);
	fillMatrix(matrixC_2D_array, 0);
	cout << "Multiplying Matrix A:" << endl;
	printMatrix(matrixA_2D_array);
	cout << "With Matrix B" << endl;
	printMatrix(matrixB_2D_array);
	multMatrices(matrixA_2D_array, matrixB_2D_array, matrixC_2D_array);
	cout << "Long Matrix Mutliplication (A * B) Result:" << endl;
	printMatrix(matrixC_2D_array);
	cout << "----------------------" << endl << endl;

	//Question #6 
	cout << "-----------Question 6-------" << endl << endl;
	
	//Reinitialize matrices
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

	cout << "Multiplying Matrix A and B with recursive Algorithm" << endl << endl;
	//matrixMultrecursive(5, 5, matrixA_2D_array, 5, 5, matrixB_2D_array, matrixC_2D_array);
	matrixMultrecursive(matrixA_2D_array, matrixB_2D_array, matrixC_2D_array, 5, 5, 5, 5);
	cout << "Recursive Mutliplication (A * B) Result:" << endl;
	printMatrix(matrixC_2D_array);
	cout << "----------------------" << endl << endl;



	//Question #7
	cout << "-----------Question 7-------" << endl << endl;

	int matrixA[rows][cols];
	int matrixB[rows][cols];
	int matrixC[rows][cols];

	int (*matrixA_ptr)[rows][cols];
	matrixA_ptr = &matrixA;

	int rows_n_cols = 5;
	int *ptr_rows_n_cols = &rows_n_cols;

	//Fill Matrix Using Pointers
	fillMatrixPtr(matrixA_ptr, rows_n_cols, rows_n_cols);
	cout << "Matrix Before Transpose Operation" << endl;

	//Print Matrix Using Pointers
	printMatrixPtr(matrixA_ptr, rows_n_cols, rows_n_cols);

	//Transpose Matrix Using Pointers
	transposeMatrix(matrixA_ptr, rows_n_cols, rows_n_cols);

	cout << "Matrix After Transpose Operation" << endl;
	printMatrixPtr(matrixA_ptr, rows_n_cols, rows_n_cols);
	cout << "----------------------" << endl << endl;

	//Question #8
	cout << "-----------Question 8-------" << endl << endl;
	int matrixA1D[rows*cols];

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

