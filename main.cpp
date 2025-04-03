/*
* Name: ALBRIGHT_PARKER_LAB08
* Description: This program does various matrix operations from a file
* Inputs: File with name specified by user
* Outputs: Command prompt matrices
* Collaborators: None
* Sources: None
* Author: Parker Albright
* Creation Date: 4/3/2025
*/
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

// Updates a single cell in the given matrix
void updateMatrixCell(std::vector<std::vector<int>>& matrix, int row, int col, int newValue) {
    int nRows = matrix.size();
    int nCols = matrix[0].size();

    matrix[row][col] = newValue;

    std::cout << "Matrix after updating row " << row << ", column " << col
        << " with value " << newValue << ":\n";
    for (const auto& r : matrix) {
        for (int val : r) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }

}

// Prints the matrix to the command prompt
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            std::cout << std::setw(4) << val;
        }
        std::cout << std::endl;
    }
}

// Swaps two rows of a given matrix
void swapRows(vector<vector<int>> A, int row1, int row2)
{
    int n = A.size();
    std::swap(A[row1], A[row2]);

    std::cout << "Matrix after swapping row " << row1 << " and row " << row2 << ":\n";
    for (const auto& row : A) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }

    printMatrix(A);
}

// Swaps to collumns of the given matrix
void swapCols(vector<vector<int>> A, int col1, int col2)
{
    int n = A.size();
    std::swap(A[col1], A[col2]);

    std::cout << "Matrix after swapping column " << col1 << " and column " << col2 << ":\n";
    for (const auto& row : A) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }

    printMatrix(A);
}

// Adds two matrices together
void additionMatrices(const vector<vector<int>> A, const vector<vector<int>> B)
{
    int n = A.size();

    vector<vector<int>> matrix(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = A[i][j] + B[i][j];
        }
    }

    printMatrix(matrix);
}

// Multiplies two matrices together
void multiplyMatrices(const vector<vector<int>> A, const vector<vector<int>> B)
{
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    std::vector<std::vector<int>> matrix(rowsA, std::vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                matrix[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printMatrix(matrix);
}

// Adds the diagonals of a matrix
void sumDiagonals(const vector<vector<int>>& matrix)
{
    int n = matrix.size();
    int mainDiagonal = 0;
    int secondaryDiagonal = 0;

    for (int i = 0; i < n; ++i) {
        mainDiagonal += matrix[i][i];               // Top-left to bottom-right
        secondaryDiagonal += matrix[i][n - 1 - i];  // Top-right to bottom-left
    }

    std::cout << "Main Diagonal Sum: " << mainDiagonal << std::endl;
    std::cout << "Secondary Diagonal Sum: " << secondaryDiagonal << std::endl;
}

// Reads and constructs a matrix from the file 
std::vector<std::vector<int>> readMatrix(std::ifstream& file, int n) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> matrix[i][j];
        }
    }
    return matrix;
}

// Runs the file
int main() {
    std::string filename;
    std::cout << "Enter file name: ";
    std::cin >> filename;

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    int n;
    file >> n;

    if (n <= 0) {
        std::cerr << "Invalid matrix size." << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> matrixA = readMatrix(file, n);
    std::vector<std::vector<int>> matrixB = readMatrix(file, n);

    std::cout << "\nMatrix A:\n";
    printMatrix(matrixA);

    std::cout << "\nMatrix B:\n";
    printMatrix(matrixB);

    std::cout << "\nMatrix A + B\n";
    additionMatrices(matrixA, matrixB);

    std::cout << "\nMatrix A * B\n";
    multiplyMatrices(matrixA, matrixB);

    cout << endl;

    cout << "Matrix A Diagonals" << endl;
    sumDiagonals(matrixA);
    cout << endl;
    cout << "Matrix B Diagonals" << endl;
    sumDiagonals(matrixB);
    cout << endl;

    cout << "Swap rows of matrix A" << endl;
    swapRows(matrixA, 0, 1);

    cout << "Swap rows of matrix B" << endl;
    swapRows(matrixB, 0, 1);

    cout << "Swap columns of matrix A" << endl;
    swapCols(matrixA, 0, 1);

    cout << "Swap columns of matrix B" << endl;
    swapCols(matrixB, 0, 1);

    cout << "Updating Matrix A" << endl;
    updateMatrixCell(matrixA, 0, 1, 3);

    cout << "Updating Matrix B" << endl;
    updateMatrixCell(matrixB, 1, 0, 2);

    return 0;
}
