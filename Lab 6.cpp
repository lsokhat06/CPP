#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>

// Виводимо матрицю у форматованому вигляді
void printMatrix(std::vector<std::vector<double>>& matrix) {
    for (const std::vector<double>& row: matrix) {
        for (const double value : row) {
            std::cout << std::setw(10) << std::setprecision(4) << std::fixed << value << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Читаємо матрицю з файлу
std::vector<std::vector<double>> readMatrixFromFile() {
    std::string path;
    std::cout << "Enter the path to your file: ";
    std::getline(std::cin, path);

    std::vector<std::vector<double>> matrix;
    std::ifstream file(path);

    if (!file) {
        std::cerr << "Could not open your file by path " + path;
        return matrix;
    }

    std::string line;
    // Отримуємо рядок і перетворюємо строки в числа за допомогою std::istringstream
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::vector<double> row;
        double number;

        while (stream >> number) {
            row.push_back(number);
        }

        matrix.push_back(row);
    }

    file.close();
    return matrix;
}

void gaussianElimination(std::vector<std::vector<double>>& matrix) {
    int size = matrix.size();

    // Проходимо по всіх рядках матриці
    for (int i = 0; i < size; ++i) {

        // Ініціалізуємо максимальний елемент
        double maxEl = abs(matrix[i][i]);
        // Ініціалізуємо номер рядка з максимальним елементом
        int maxRow = i;

        // Шукаємо максимальний елемент нижче даного рядка
        for (int k = i + 1; k < size; ++k) {
            if (abs(matrix[k][i]) > maxEl) {
                maxEl = abs(matrix[k][i]);
                maxRow = k;
            }
        }

        // Міняємо рядок, що містить максимальний елемент, місцями з даним
        std::swap(matrix[maxRow], matrix[i]);

        // Обнуляємо елементи під даним рядком
        for (int k = i + 1; k < size; ++k) {
            double coeff = matrix[k][i] / matrix[i][i];
            // Віднімаємо даний рядок, помножений на коефіцієнт, із рядка k
            for (int j = i; j < size; ++j) {
                matrix[k][j] -= coeff * matrix[i][j];
            }
        }
    }
}

// Рахуємо кількість рядків, у яких середнє арифметичне менше заданого значення
void rowsAvgLessThan(std::vector<std::vector<double>>& matrix) {
    double value;
    std::cout << "Enter the value to compare: ";
    std::cin >> value;

    int count = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        // std::accumulate знаходить суму всіх елементів між двома ітераторами
        if ((std::accumulate(matrix[i].begin(), matrix[i].end(), 0.0) / matrix[i].size()) < value) {
            count++;
        }
    }

    std::cout << std::endl << "Number of rows, whose mean is smaller than the value, is " << count;
}

int main() {
    std::vector<std::vector<double>> matrix = readMatrixFromFile();
    std::cout << std::endl << "Your matrix: " << std::endl;
    printMatrix(matrix);

    gaussianElimination(matrix);
    std::cout << std::endl << "Transformed matrix: " << std::endl;
    printMatrix(matrix);

    rowsAvgLessThan(matrix);
}