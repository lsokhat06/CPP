#include <iostream>

// �������� �������
void print_matrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// ������� ���������� �������� ������� �������
void sort_diagonal(int** matrix, int size) {
    print_matrix(matrix, size);
    // ��� n �������� ��������� (n - 1) ��������
    for (int iterations = 0; iterations < size - 1; ++iterations) {
        bool swapped = false;
        // ������� ���� ����� �������� ������� ������� ��� ������������, 
        // ���� ����� ������� ���������� ����� �������
        for (int i = 0; i < size - iterations - 1; ++i) {
            // ���� ������� �� �������� ������ � ��� ����� �������� ������ - ������ ������
            if (matrix[i][i] > matrix[i + 1][i + 1]) {
                std::swap(matrix[i][i], matrix[i + 1][i + 1]);
                swapped = true;
            }
        }
        // �����������: ���� �������� �� �������������� - �������� ����������� - ��������
        if (!swapped) { break; }
    }
    // ̳����� ������ ��������� � ��������� ��������
    std::swap(matrix[0][0], matrix[size - 1][size - 1]);
    print_matrix(matrix, size);
}

// �������� ���'��� �� ������� size x size
int** allocate_matrix(int size) {
    int** matrix = new int* [size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) { matrix[i][j] = rand() % 100; }
    }
    return matrix;
}

// ϳ��� ��������� ������ ��������� ���'���
void deallocate_matrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    int size = 8;
    int** matrix = allocate_matrix(size);
    sort_diagonal(matrix, size);
    deallocate_matrix(matrix, size);
}