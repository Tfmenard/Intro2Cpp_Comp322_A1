#pragma once
const int rows = 5;
const int cols = 5;

int matrix1D_Size = rows*cols;


const int * rows_ptr = &rows;
const int * cols_ptr = &cols;

class main
{

public:
	main();
	~main();

	void fillMatrix(int matrix[rows][cols]);

	void PrintMatrix(int matrix[rows][cols]);

	void transposeMatrix(int matrix[rows][cols]);

	void swapMatrixElements(int &matrix, int &row, int &col);

	void fillMatrixRowsWithConstants(int matrix[rows][cols]);

	int multMatrices(int matrixA[rows][cols], int matrixB[rows][cols]);

};

