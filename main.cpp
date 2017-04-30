#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void initializeMatrix(int**& matrix, int rows, int columns);
void fillMatrixUserInput(int**& matrix, int rows, int columns);
void fillMatrixFromFile(int**& matrix, int rows, int columns, ifstream &infile);
void matrixAddition(int**& matrix1, int**& matrix2, int rows, int columns);
void matrixSubtraction(int**& matrix1, int**& matrix2, int rows, int columns);
void matrixMultiplication(int**& matrix1, int**& matrix2, int rows1, int columns1, int columns2);
void transposeMatrix(int**& matrix, int rows, int columns);

int main() {
    ifstream infile;
    string fileName;
    int rows1, columns1, rows2, columns2, menuChoice;
    int** matrix1;
    int** matrix2;

    cout << "Would you like to read from a file, or enter your matrices by hand?\n";
    cout << "(1) File, (2) By Hand: ";
    cin >> menuChoice;

    switch (menuChoice) {
        case 1:
            cout << "Enter the file you wish to open: ";
            cin >> fileName;
            infile.open(fileName);
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
            break;
        case 2:
            cout << "Enter a number of rows for the first matrix: ";
            cin >> rows1;
            cout << "Enter a number of columns for the first matrix: ";
            cin >> columns1;

            initializeMatrix(matrix1, rows1, columns1);
            fillMatrixUserInput(matrix1, rows1, columns1);

            cout << "Enter a number of rows for the second matrix: ";
            cin >> rows2;
            cout << "Enter a number of columns for the second matrix: ";
            cin >> columns2;

            initializeMatrix(matrix2, rows2, columns2);
            fillMatrixUserInput(matrix2, rows2, columns2);

            break;
        default:
            cout << "Error: Invalid Input\n";
            return 0;
    }

    do {
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
                if (rows1 != rows2 && columns1 != columns2) {
                    cout << "The Matrices you entered cannot be added.\n";
                } else {
                    matrixAddition(matrix1, matrix2, rows1, rows2);
                }
                break;
            case 2:
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
                cout << "Would you like to attempt to multiply Matrix 1 X Matrix 2, or Matrix 2 X Matrix 1?";
                cout << "Enter 1 for (M1xM2) or 2 for (M2xM1): ";
                cin >> menuChoice;
                if (menuChoice == 1 && columns1 == rows2) {
                    matrixMultiplication(matrix1, matrix2, rows1, columns1, columns2);
                } else if (menuChoice == 2 && columns1 == rows2) {
                    matrixMultiplication(matrix2, matrix1, rows2, columns2, columns1);
                } else {
                    cout << "The Matrices you entered cannot be multiplied in this order.\n";
                }
                break;
            case 4:
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
    } while (menuChoice != 5);

    //TODO: Release Dynamically Allocated Memory

    return 0;
}

void initializeMatrix(int**& matrix, int rows, int columns) {
    matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        *(matrix + i) = new int[columns];
    }
}

void fillMatrixUserInput(int**& matrix, int rows, int columns) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            cout << "Enter a value for position [" << r << "," << c << "]: ";
            cin >> *(*(matrix + r) + c);
        }
    }
}

void fillMatrixFromFile(int**& matrix, int rows, int columns, ifstream &infile) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            infile >> *(*(matrix + r) + c);
        }
    }
}

void matrixAddition(int**& matrix1, int**& matrix2, int rows, int columns) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            cout << setw(4) << *(*(matrix1 + r) + c) + *(*(matrix2 + r) + c) << " ";
        }
        cout << "\n";
    }
}

void matrixSubtraction(int**& matrix1, int**& matrix2, int rows, int columns) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            cout << setw(4) << *(*(matrix1 + r) + c) - *(*(matrix2 + r) + c);
        }
        cout << "\n";
    }
}

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

void transposeMatrix(int**& matrix, int rows, int columns) {
    for (int r = 0; r < columns; ++r) {
        for (int c = 0; c < rows; ++c) {
            cout << setw(4) << *(*(matrix + c) + r);
        }
        cout << "\n";
    }
}
