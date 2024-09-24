#include <iostream>
#include <string>

// Інформація про кожен окремий поїзд
struct TrainInfo {
public:
    int identifier;
    std::string route;
    std::string arrivalTime;
    std::string departureTime;
};

// Розклад, що містить вказівник на динамічний масив TrainInfo
struct Schedule {
public:
    TrainInfo* trains;
    int quantity;

    void print(std::string arrivalTime) {
        std::cout << "Printing information about trains with time of arrival " << arrivalTime << "...\n\n";
        for (int i = 0; i < quantity; ++i) {
            // Пропускаємо всі елементи з часом прибуття, який не дорівнює заданому
            if (trains[i].arrivalTime != arrivalTime) {
                continue;
            }

            std::cout << "Number: " << trains[i].identifier << "\n";
            std::cout << "Route: " << trains[i].route << "\n";
            std::cout << "Time of departure: " << trains[i].departureTime << "\n";
            std::cout << "Time of arrival: " << trains[i].arrivalTime << "\n\n";
        }
    }

    // Видаляємо динамічно виділений масив при виході з області видимості
    ~Schedule() {
        delete[] trains;
    }
};

int main() {
    srand(time(NULL));

    Schedule schedule;

    schedule.quantity = 5;
    schedule.trains = new TrainInfo[5] {
        {rand() % 1000, "Lviv - Kharkiv", "10:00", "5:00"},
        {rand() % 1000, "Odessa - Kharkiv", "14:00", "11:00"},
        {rand() % 1000, "Kherson - Kharkiv", "17:00", "12:00"},
        {rand() % 1000, "Ivano-Frankivs'k - Kharkiv", "14:00", "7:00"},
        {rand() % 1000, "Kirovograd - Kharkiv", "14:00", "9:00"}
    };
    
    std::cout << "Enter the time: ";
    std::string time;
    std::getline(std::cin, time);

    schedule.print(time);
}
