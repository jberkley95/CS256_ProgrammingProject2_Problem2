/**
    CS-256
    MatrixOperations.cpp
    Purpose: Performs matrix operations on two 2D Matrices. Operations include addition, subtraction,
    multiplication, and transpose.

    @author John Berkley
    @version 1.0 4/22/2017
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

/**
 * Dynamically allocated passed matrix with number of rows and columns
 *
 * @param matrix to be initialized
 * @param rows of the matrix
 * @param columns of the matrix
 */
void initializeMatrix(int**& matrix, int rows, int columns);
/**
 * Fills matrix with input from the user
 *
 * @param matrix to be filled
 * @param rows of the matrix
 * @param columns of the matrix
 */
void fillMatrixUserInput(int**& matrix, int rows, int columns);
/**
 * Fills matrix with input from infile
 *
 * @param matrix to be filled
 * @param rows of the matrix
 * @param columns of the matrix
 * @param infile to read input from
 */
void fillMatrixFromFile(int**& matrix, int rows, int columns, ifstream &infile);
/**
 * Adds matrix1 to matrix2 and displays new matrix
 *
 * @param matrix1 to be added
 * @param matrix2 to be added
 * @param rows of matrix1 and matrix2
 * @param columns of matrix1 and matrix2
 */
void matrixAddition(int**& matrix1, int**& matrix2, int rows, int columns);
/**
 * Subtracts matrix2 from matrix1 and displays new matrix
 *
 * @param matrix1 to be subtracted from
 * @param matrix2 to be subtracted from
 * @param rows of matrix1 and matrix2
 * @param columns of matrix1 and matrix2
 */
void matrixSubtraction(int**& matrix1, int**& matrix2, int rows, int columns);
/**
 * Multiplies matrix1 by matrix2 and displays new matrix
 *
 * @param matrix1 to be multiplied
 * @param matrix2 to be multiplied
 * @param rows1 of first matrix
 * @param columns1 of first matrix
 * @param columns2 of second matrix
 */
void matrixMultiplication(int**& matrix1, int**& matrix2, int rows1, int columns1, int columns2);
/**
 * Transposes matrix and displays new matrix
 *
 * @param matrix to be transposed
 * @param rows of the matrix
 * @param columns of the matrix
 */
void transposeMatrix(int**& matrix, int rows, int columns);

int main() {
    //declare variables and matrices
    ifstream infile;
    string fileName;
    int rows1, columns1, rows2, columns2, menuChoice;
    int** matrix1;
    int** matrix2;

    //Give user choice to read from a file or enter data by hand
    cout << "Would you like to read from a file, or enter your matrices by hand?\n";
    cout << "(1) File, (2) By Hand: ";
    cin >> menuChoice;

    //Read in data depending on user choice
    switch (menuChoice) {
        case 1:
            cout << "Enter the file you wish to open: ";
            cin >> fileName;
            infile.open(fileName.c_str());

            //If file is opened successfully, read in R/C, then data for both matrices
            if (infile.is_open()) {
                infile >> rows1 >> columns1;
                initializeMatrix(matrix1, rows1, columns1);
                fillMatrixFromFile(matrix1, rows1, columns1, infile);
                infile >> rows2 >> columns2;
                initializeMatrix(matrix2, rows2, columns2);
                fillMatrixFromFile(matrix2, rows2, columns2, infile);
            } else {
                cout << "Error: File Not Found\n";
                return 0;
            }
            infile.close();
            break;
        case 2:
            //Read in R/C for matrix 1
            cout << "Enter a number of rows for the first matrix: ";
            cin >> rows1;
            cout << "Enter a number of columns for the first matrix: ";
            cin >> columns1;

            //Initialize and Fill Matrix 1
            initializeMatrix(matrix1, rows1, columns1);
            fillMatrixUserInput(matrix1, rows1, columns1);

            //Read in R/C for matrix 2
            cout << "Enter a number of rows for the second matrix: ";
            cin >> rows2;
            cout << "Enter a number of columns for the second matrix: ";
            cin >> columns2;

            //Initialize and Fill Matrix 2
            initializeMatrix(matrix2, rows2, columns2);
            fillMatrixUserInput(matrix2, rows2, columns2);

            break;
        default:
            cout << "Error: Invalid Input\n";
            return 0;
    }


    //Repeat while user doesn't wish to exit
    do {
        //Display menu choices
        cout << "Choose an operation to perform with your two Matrices:\n";
        cout << "1) Matrix Addition\n";
        cout << "2) Matrix Subtraction\n";
        cout << "3) Matrix Multiplication\n";
        cout << "4) Transpose A Matrix\n";
        cout << "5) Quit\n";
        cout << "Enter your choice: ";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1:
                //Check if Matrix dimensions match, if they do, add them and display output
                if (rows1 != rows2 && columns1 != columns2) {
                    cout << "The Matrices you entered cannot be added.\n";
                } else {
                    matrixAddition(matrix1, matrix2, rows1, rows2);
                }
                break;
            case 2:
                //Give user a choice of which way they would like to subtract and check if the matrices match
                //If they do, perform and display operation
                cout << "Would you like to attempt to subtract Matrix 1 - Matrix 2, or Matrix 2 - Matrix 1?\n";
                cout << "Enter 1 for (M1-M2) or 2 for (M2-M1): ";
                cin >> menuChoice;
                if (menuChoice == 1 && rows1 == rows2 && columns1 == columns2) {
                    matrixSubtraction(matrix1, matrix2, rows1, rows2);
                } else if (menuChoice == 2 && rows1 == rows2 && columns1 == columns2) {
                    matrixSubtraction(matrix2, matrix1, rows1, rows2);
                } else {
                    cout << "The Matrices you entered cannot be subtracted.\n";
                }
                break;
            case 3:
                //Give user a choice of which way they would like to multiply and check if the dimensions allow it
                //If they do, multiply and display output matrix
                cout << "Would you like to attempt to multiply Matrix 1 X Matrix 2, or Matrix 2 X Matrix 1?";
                cout << "Enter 1 for (M1xM2) or 2 for (M2xM1): ";
                cin >> menuChoice;
                if (menuChoice == 1 && columns1 == rows2) {
                    matrixMultiplication(matrix1, matrix2, rows1, columns1, columns2);
                } else if (menuChoice == 2 && columns2 == rows1) {
                    matrixMultiplication(matrix2, matrix1, rows2, columns2, columns1);
                } else {
                    cout << "The Matrices you entered cannot be multiplied in this order.\n";
                }
                break;
            case 4:
                //Ask user which matrix they would like to transpose, get input, and transpose the matrix and display
                cout << "Would you like to see the Transpose of Matrix 1 or Matrix 2 (Enter 1 or 2): ";
                cin >> menuChoice;
                if (menuChoice == 1) {
                    transposeMatrix(matrix1, rows1, columns1);
                } else if (menuChoice == 2) {
                    transposeMatrix(matrix2, rows2, columns2);
                } else {
                    cout << "Error: Invalid Input\n";
                }
                break;
            case 5:
                cout << "Goodbye.\n";
                break;
            default:
                cout << "Invalid Input: Please Try Again";
                break;
        }
        //Pause and clear screen after each menu option is executed
        cout << "\n";
        system("pause");
        system("cls");
    } while (menuChoice != 5);

    //Release dynamically allocated memory
    for (int i = 0; i < rows1; ++i) {
        delete [] matrix1[i];
    }
    delete [] matrix1;

    for (int i = 0; i < rows2; ++i) {
        delete [] matrix2[i];
    }
    delete [] matrix2;

    matrix1 = NULL;
    matrix2 = NULL;

    return 0;
}

//Dynamically allocated passed matrix with number of rows and columns
void initializeMatrix(int**& matrix, int rows, int columns) {
    matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        *(matrix + i) = new int[columns];
    }
}

//Fills matrix with input from the user
void fillMatrixUserInput(int**& matrix, int rows, int columns) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            cout << "Enter a value for position [" << r << "," << c << "]: ";
            cin >> *(*(matrix + r) + c);
        }
    }
}

//Fills matrix with input from infile
void fillMatrixFromFile(int**& matrix, int rows, int columns, ifstream &infile) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            infile >> *(*(matrix + r) + c);
        }
    }
}

//Adds matrix1 to matrix2 and displays new matrix
void matrixAddition(int**& matrix1, int**& matrix2, int rows, int columns) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            cout << setw(4) << *(*(matrix1 + r) + c) + *(*(matrix2 + r) + c) << " ";
        }
        cout << "\n";
    }
}

//Subtracts matrix2 from matrix1 and displays new matrix
void matrixSubtraction(int**& matrix1, int**& matrix2, int rows, int columns) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            cout << setw(4) << *(*(matrix1 + r) + c) - *(*(matrix2 + r) + c);
        }
        cout << "\n";
    }
}

//Multiplies matrix1 by matrix2 and displays new matrix
void matrixMultiplication(int**& matrix1, int**& matrix2, int rows1, int columns1, int columns2) {
    int temp = 0;

    for(int i = 0; i < rows1; ++i) {
        for(int j = 0; j < columns2; ++j) {
            for(int k = 0; k < columns1; ++k) {
                temp += *(*(matrix1 + i) + k) * *(*(matrix2 + k) + j);
            }

            cout << setw(4) << temp;
            temp = 0;
        }
        cout << "\n";
    }
}

//Transposes matrix and displays new matrix
void transposeMatrix(int**& matrix, int rows, int columns) {
    for (int r = 0; r < columns; ++r) {
        for (int c = 0; c < rows; ++c) {
            cout << setw(4) << *(*(matrix + c) + r);
        }
        cout << "\n";
    }
}
