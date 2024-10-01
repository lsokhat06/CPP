#include <iostream>
#include <algorithm>

// Оскільки лабораторна духе схожа на другу, деякі функції взяв звідти

// Виведення матриці
void print_matrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Виділяємо пам'ять під матрицю size x size і заповнюємо її випадковими числами
int** allocate_and_fill(int size) {
    int** matrix = new int* [size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) { matrix[i][j] = (rand() % 90) + 10; }
    }
    return matrix;
}

// Обробка матриці: виведення до сортування, сортування, виведення після сортування
void sort_and_print(int** matrix, int size) {
    // Відкидаємо занадто малі матриці
    if (size < 2) {
        std::cout << "The matrix is too small!";
        return;
    }

    std::cout << "Before sorting:\n";
    print_matrix(matrix, size);

    std::sort(matrix[1], matrix[1] + size);
    std::cout << "After sorting:\n";
    print_matrix(matrix, size);
}

// Пошук максимального елемента в другому рядку (окрема функція, щоб працювало для невідсортованих матриць)
void find_largest(int** matrix, int size) {
    if (size < 2) {
        std::cout << "The matrix is too small!";
        return;
    }

    int max = matrix[1][0];

    for (int i = 0; i < size; ++i) {
        if (matrix[1][i] > max) {
            max = matrix[1][i];
        }
    }

    std::cout << "Max element in the second row: " << max << "\n";
}

// Після закінчення роботи звільняємо пам'ять
void deallocate_matrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    srand(time(NULL));
    int size = 10;

    int** matrix = allocate_and_fill(size);
    sort_and_print(matrix, size);
    find_largest(matrix, size);
    deallocate_matrix(matrix, size);
}