#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "functions.h"

// Заповнюємо масив випадковими числами від -100 до 100
#define RANDOM_FILL(vec, N) { \
    std::srand(std::time(0)); \
    for (int i = 0; i < N; ++i) { \
        vec.push_back(std::rand() % 201 - 100); \
    } \
}

// Виводимо масив
#define PRINT_VECTOR(vec) { \
    std::cout << "Vector: "; \
    for (const auto& elem : vec) { \
        std::cout << elem << " "; \
    } \
    std::cout << std::endl; \
}

// Шукаємо позицію елемента з мінімальним модулем
#define FIND_MIN_ABS_POSITION(vec, pos) { \
    pos = 0; \
    for (int i = 1; i < vec.size(); ++i) { \
        if (std::abs(vec[i]) < std::abs(vec[pos])) { \
            pos = i; \
        } \
    } \
}

// Шукаємо суму модулів елементів за першим від'ємним
#define SUM_ABS_BEYOND_FIRST_NEGATIVE(vec, sum) { \
    sum = 0; \
    bool found_negative = false; \
    for (const auto& elem : vec) { \
        if (found_negative) { \
            sum += std::abs(elem); \
        } \
        if (elem < 0 && !found_negative) { \
            found_negative = true; \
        } \
    } \
}

// Стискаємо масив, видаляючи елементи, модуль яких входить в проміжок [a; b], кінець заповнюємо нулями
#define COMPRESS_ARRAY(vec, a, b) { \
    std::vector<int> temp; \
    int count_deleted = 0; \
    for (const auto& elem : vec) { \
        if (std::abs(elem) < a || std::abs(elem) > b) { \
            temp.push_back(elem); \
        } else { \
            ++count_deleted; \
        } \
    } \
    temp.insert(temp.end(), count_deleted, 0); \
    vec = temp; \
}
