#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>

struct Student {
	std::string name;
	std::string surname;
	std::vector<int> grades;

    // 6. Знайти середній бал для всіх студентів з використанням std::accumulate
    double getAverage() const {
        int cumulative = std::accumulate(grades.begin(), grades.end(), 0);
        return grades.empty() ? 0 : (double)(cumulative) / grades.size();
    }

    bool operator==(const Student& other) const {
        return name == other.name && surname == other.surname && grades == other.grades;
    }
};

class Students {
private:
    std::vector<Student> students;

public:
    Students(std::vector<Student> provided) : students(provided) {}
    Students() {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    // 1. Забезпечити для контейнера можливість зчитування з файлу і запису в файл з використанням ітераторів потоків.
    void readFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile) {
            std::cerr << "Could not open the file for reading: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream lineStream(line);
            Student student;
            lineStream >> student.name >> student.surname;

            std::copy(std::istream_iterator<int>(lineStream), std::istream_iterator<int>(), std::back_inserter(student.grades));

            students.push_back(student);
        }

        inputFile.close();
    }

    // 1. Забезпечити для контейнера можливість зчитування з файлу і запису в файл з використанням ітераторів потоків.
    void writeToFile(const std::string& filename) const {
        std::ofstream outputFile(filename);
        if (!outputFile) {
            std::cerr << "Could not open the file for writing: " << filename << std::endl;
            return;
        }

        for (const auto& student : students) {
            outputFile << student.name << " " << student.surname;

            std::copy(student.grades.begin(), student.grades.end(), std::ostream_iterator<int>(outputFile, " "));
            outputFile << std::endl;
        }

        outputFile.close();
    }

    void printStudents() const {
        for (const auto& student : students) {
            std::cout << "Name: " << student.name << ", Surname: " << student.surname << ", Grades: ";
            for (const auto& grade : student.grades) {
                std::cout << grade << " ";
            }
            std::cout << std::endl;
        }
    }

    // 2. Забезпечити для контейнера сортування за прізвищем студента
    void sortBySurnames() {
        std::sort(students.begin(), students.end(), [](const Student& first, const Student& second) {
            return first.surname < second.surname;
        });
    }

    // 2. а також сортування за його середнім балом за останню сесію
    void sortByAverages() {
        std::sort(students.begin(), students.end(), [](const Student& first, const Student& second) {
            return first.getAverage() < second.getAverage();
        });
    }

    // 3, 4. Створити окремий вектор зі студентами, чий середній бал більше 4
    Students getGoodStudents() {
        std::vector<Student> goodStudents;

        std::copy_if(students.begin(), students.end(), std::back_inserter(goodStudents),
            [](const Student& student) {
                return student.getAverage() > 4;
        });

        return Students(goodStudents);
    }

    // 5. Дізнатися кількість студентів з середнім балом вище заданого
    int countAbove(double threshold) const {
        return std::count_if(students.begin(), students.end(),
            [threshold](const Student& student) {
                return student.getAverage() > threshold;
        });
    }

    // 7. Перевірити, чи входить вектор, отриманий у кроці 3, у вихідний вектор
    // (узагальнено для будь-яких контейнерів)
    bool isSubsetOf(const Students& other) const {
        for (const auto& student : students) {
            if (std::find(other.students.begin(), other.students.end(), student) == other.students.end()) {
                return false;
            }
        }
        return true;
    }

};

int main() {
    Students students;
    
    students.addStudent({ "John", "Smith", { 3, 3, 3 } });
    students.addStudent({ "Jane", "Doe", { 4, 5, 5 } });

    std::cout << "Initial container:\n";
    students.printStudents();

    students.sortBySurnames();
    std::cout << "\nSorted by surname:\n";
    students.printStudents();

    students.sortByAverages();
    std::cout << "\nSorted by average grade:\n";
    students.printStudents();

    Students good = students.getGoodStudents();
    std::cout << "\nStudents with average greater than 4:\n";
    good.printStudents();

    std::cout << "\nIs this container a subset of original one? " << (good.isSubsetOf(students) ? "true" : "false");

    std::cout << "\nHow many students with average above 3? " << students.countAbove(3.0);
}