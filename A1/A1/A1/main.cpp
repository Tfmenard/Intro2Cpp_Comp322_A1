#include "main.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

void fillMatrix(int matrix[rows][cols])
{
	/* initialize random seed: */
	srand(time(NULL));

	for (int row = 0; row < rows; row++) 
	{
		for (int col = 0; col < cols; col++)
		{
			/* generate number between 1 and 10: */
			matrix[row][col] = rand() % 10 + 1;
			//cout << "row = " << row << " ";
			//cout << "col = " << col << " ";
			//cout << matrix[row][col] << endl;
		}
	}

}

void fillMatrixPtr(int * ptr_matrix[rows][cols], int &rows, int &cols)
{
	/* initialize random seed: */
	srand(time(NULL));

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			/* generate number between 1 and 10: */
			*ptr_matrix[row][col] = rand() % 10 + 1;
			//cout << "row = " << row << " ";
			//cout << "col = " << col << " ";
			//cout << matrix[row][col] << endl;
		}
	}

}

void fillMatrixRowsWithConstants(int matrix[rows][cols], int constant)
{

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			//fill all elements of the same row with their row number
			if (constant == 2)
			{
				matrix[row][col] = constant;
			}
			else
			{
				matrix[row][col] = row;
			}
		}
	}

}

void PrintMatrix(int matrix[rows][cols])
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

void PrintMatrixPtr(int *matrix[rows][cols], int *rows, int *cols)
{
	for (int row = 0; row < *rows; row++)
	{
		cout << "row " << row << ": ";
		for (int col = 0; col < *cols; col++)
		{
			cout << *matrix[row][col] << " ";
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

void swapMatrixElementsPtr(int * matrix[rows][cols], int &row, int &col)
{
	int * temp;
	temp = matrix[row][col];
	matrix[row][col] = matrix[col][row];
	matrix[col][row] = temp;
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

void transposeMatrix(int * matrix[rows][cols], int *rows, int *cols)
{
	for (int row = 0; row < *rows - 1; row++)
	{
		int col_start_index = row + 1;

		for (int col = col_start_index; col < *cols; col++)
		{
			swapMatrixElementsPtr(matrix, row, col);
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
	int row1, int col1, int A[rows][cols],
	int row2, int col2, int B[rows][cols],
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



int main()
{
	int *matrixA[rows][cols];
	int *matrixB[rows][cols];
	int *matrixC[rows][cols];


	int rows_n_cols = 5;
	int *ptr_rows_n_cols = &rows_n_cols;
	/*fillMatrixRowsWithConstants(matrixA, 2);
	fillMatrixRowsWithConstants(matrixB, 2);
	fillMatrixRowsWithConstants(matrixC, 2);*/
	fillMatrixPtr(matrixA, rows_n_cols, rows_n_cols);
	fillMatrixPtr(matrixB, rows_n_cols, rows_n_cols);
	fillMatrixPtr(matrixC, rows_n_cols, rows_n_cols);
	//PrintMatrix(matrixA);
	//transposeMatrix(matrixA);
	PrintMatrixPtr(matrixB, ptr_rows_n_cols, ptr_rows_n_cols);
	//multMatrices(matrixA, matrixB, matrixC);
	cout << "Matrix A" << " ";
	cout << endl;
	PrintMatrixPtr(matrixC, ptr_rows_n_cols, ptr_rows_n_cols);

	//matrixMultrecursive(5, 5, matrixA, 5, 5, matrixB, matrixC);
	return 0;
}

