#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Matrix {
protected:
    std::vector<std::vector<T>> mat;
    int rows;
    int cols;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        std::cout << "\Called Matrix(" << r << ", " << c << ")\n";
        mat.resize(r, std::vector<T>(c));
    }

    virtual void input() = 0;
    virtual void output() = 0;
};

template <typename T>
class ProcessMatrix : public Matrix<T> {
public:
    ProcessMatrix(int r, int c) : Matrix<T>(r, c) {
        std::cout << "\Called ProcessMatrix(" << r << ", " << c << ")\n";
    }

    void input() override {
        std::cout << "Enter the elements of matrix " << this->rows << "x" << this->cols << ":\n";
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                std::cin >> this->mat[i][j];
            }
        }
    }

    void output() override {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                std::cout << this->mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void sortDiagonal() {
        if (this->rows != this->cols) {
            throw std::runtime_error("Matrix is not square.");
        }

        std::vector<T> diagonal;

        for (int i = 0; i < this->rows; ++i) {
            diagonal.push_back(this->mat[i][i]);
        }

        std::sort(diagonal.begin(), diagonal.end());

        for (int i = 0; i < this->rows; ++i) {
            this->mat[i][i] = diagonal[i];
        }
    }

    void swapInDiagonal() {
        if (this->rows != this->cols) {
            throw std::runtime_error("Matrix is not square.");
        }

        T mmin = this->mat[0][0];
        T mmax = this->mat[0][0];
        int minIdx = 0, maxIdx = 0;

        for (int i = 0; i < this->rows; ++i) {
            if (this->mat[i][i] < mmin) {
                mmin = this->mat[i][i];
                minIdx = i;
            }
            if (this->mat[i][i] > mmax) {
                mmax = this->mat[i][i];
                maxIdx = i;
            }
        }

        std::swap(this->mat[minIdx][minIdx], this->mat[maxIdx][maxIdx]);
    }
};

int main() {
    /*
    Enter the size of the matrix: 4
    Called Matrix(4, 4)
    Called ProcessMatrix(4, 4)
    Enter the elements of matrix 4x4:
    1
    2
    3
    4
    5
    6
    7
    8
    9
    10
    11
    12
    13
    14
    15
    16

    Your matrix:
        1 2 3 4
        5 6 7 8
        9 10 11 12
        13 14 15 16

    Your matrix after transformations:
        16 2 3 4
        5 6 7 8
        9 10 11 12
        13 14 15 1
    */


    int n;
    std::cout << "Enter the size of the matrix: ";
    std::cin >> n;

    ProcessMatrix<int> matrix(n, n);
    matrix.input();

    std::cout << "\nYour matrix:\n";
    matrix.output();

    matrix.sortDiagonal();
    matrix.swapInDiagonal();

    std::cout << "\nYour matrix after transformations:\n";
    matrix.output();

    return 0;
}
