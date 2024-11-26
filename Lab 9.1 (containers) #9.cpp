#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <map>
#include <stdexcept>

struct SequenceInfo {
    std::vector<std::pair<int, int>> quantities; // Вектор: { елемент, його кількість }
    std::map<int, int> lengths; // Хеш-таблиця: { довжина, кількість послідовностей з такою довжиною }

    // Форматований вивід масиву
    void printQuantities() {
        for (const auto& quantity : quantities) {
            /*
            * В прикладі, якщо послідовність має довжину 1, ця довжина не виводиться явно,
            * але це необхідно зробити для уникнення неоднозначності
            */
            std::cout << quantity.first << " " << quantity.second << " ";
        }
    }

    // Форматований вивід хеш-таблиці
    void printLengths() {
        if (lengths.empty()) {
            return;
        }

        /*
        * В прикладі для довжини "2" вивелось "0", тобто крім наявних значень
        * виводяться взагалі всі від 1 до максимального;
        * ітеруємо від 1 до максимального значення (в std::map ключі сортуються,
        * тому це lengths.rbegin()->first)
        */
        for (int i = 1; i <= lengths.rbegin()->first; ++i) {
            if (lengths.count(i)) {
                std::cout << i << " - " << lengths[i] << std::endl;
            }
            else {
                std::cout << i << " - 0" << std::endl;
            }
        }
    }
};

std::vector<int> getArray() {
    std::vector<int> arr;
    int quantity;
    
    std::cout << "How many elements? ";
    while (true) {
        try {
            std::cin >> quantity;
            if (std::cin.fail() || quantity < 1) {
                throw std::invalid_argument("Invalid quantity.");
            }
            break;
        }

        catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << e.what() << std::endl;
            std::cout << "One more time: ";
        }
    }

    std::cout << "Enter the elements.\n";

    for (int i = 0; i < quantity; ++i) {
        int number;
        while (true) {
            try {
                std::cin >> number;
                if (std::cin.fail()) {
                    throw std::invalid_argument("Invalid value.");
                }
                break;
            }

            catch (const std::invalid_argument& e) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << e.what() << std::endl;
                std::cout << "One more time: ";
            }
        }
        arr.push_back(number);
    }

    return arr;
}

SequenceInfo processSequence(const std::vector<int>& data) {
    if (data.empty()) {
        return {};
    }

    const int length = data.size();
    int pointer = 0;
    SequenceInfo info;

    while (pointer < length) {
        int target = data[pointer];
        int count = 0;

        while (pointer < length && data[pointer] == target) {
            count++;
            pointer++;
        }

        info.quantities.push_back(std::make_pair(target, count));
        info.lengths[count]++;
    }

    return info;
}

int main() {
    std::vector<int> data = getArray();

    SequenceInfo info = processSequence(data);
    info.printQuantities();
    std::cout << std::endl;
    info.printLengths();

    /*
    * How many elements? 14
    * Enter the elements.
    * 1 1 1 2 2 2 2 3 4 4 4 5 5 5
    * 1 3 2 4 3 1 4 3 5 3
    * 1 - 1
    * 2 - 0
    * 3 - 3
    * 4 - 1
    */
}
