#include <iostream>

// Виводимо матрицю
void print_matrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Сортуємо бульбашкою елементи головної діагоналі
void sort_diagonal(int** matrix, int size) {
    print_matrix(matrix, size);
    // Для n елементів достатньо (n - 1) ітерацій
    for (int iterations = 0; iterations < size - 1; ++iterations) {
        bool swapped = false;
        // Оскільки після кожної ітерації останній елемент вже відсортований, 
        // немає змісту постійно перебирати масив повністю
        for (int i = 0; i < size - iterations - 1; ++i) {
            // Якщо елемент за позицією менший і при цьому численно більший - міняємо місцями
            if (matrix[i][i] > matrix[i + 1][i + 1]) {
                std::swap(matrix[i][i], matrix[i + 1][i + 1]);
                swapped = true;
            }
        }
        // Оптимизація: якщо елементи не переставлялись - діагональ відсортована - виходимо
        if (!swapped) { break; }
    }
    // Міняємо місцями найменший і найбільший елементи
    std::swap(matrix[0][0], matrix[size - 1][size - 1]);
    print_matrix(matrix, size);
}

// Виділяємо пам'ять під матрицю size x size і заповнюємо її випадковими числами
int** allocate_matrix(int size) {
    int** matrix = new int* [size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) { matrix[i][j] = rand() % 100; }
    }
    return matrix;
}

// Після закінчення роботи звільняємо пам'ять
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
