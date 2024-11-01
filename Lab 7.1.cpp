#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

struct Route {
    std::string startPoint;   // Початковий пункт
    std::string endPoint;     // Кінцевий пункт
    int routeNumber;          // Номер маршруту
};

// Зчитування даних з файлу
void readRoutes(std::vector<Route>& routes, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open the file." << std::endl;
        return;
    }

    Route route;
    while (file >> route.startPoint >> route.endPoint >> route.routeNumber) {
        routes.push_back(route);
    }

    file.close();
}

// Сортування маршрутів за номерами
void sortRoutes(std::vector<Route>& routes) {
    std::sort(routes.begin(), routes.end(), [](const Route& a, const Route& b) {
        return a.routeNumber < b.routeNumber;
    });
}

// Пошук маршрутів за заданим пунктом
void findRoutes(const std::vector<Route>& routes, const std::string& point) {
    std::vector<Route> foundRoutes;

    for (const auto& route : routes) {
        if (route.startPoint == point || route.endPoint == point) {
            foundRoutes.push_back(route);
        }
    }

    if (foundRoutes.empty()) {
        std::cout << "No routes found" << std::endl;
    }

    else {
        std::ofstream outputFile("output.txt");
        for (const auto& route : foundRoutes) {
            std::cout << "Route: " << route.startPoint << " -> " << route.endPoint
                << ", Number: " << route.routeNumber << std::endl;

            outputFile << "Route: " << route.startPoint << " -> " << route.endPoint
                << ", Number: " << route.routeNumber << std::endl;
        }
        outputFile.close();
    }
}

int main() {
    std::vector<Route> routes;
    std::string filename;

    std::cout << "Enter the path to the file: ";
    std::getline(std::cin, filename);

    readRoutes(routes, filename);
    sortRoutes(routes);

    std::string point;
    std::cout << "Enter the point: ";
    std::cin >> point;

    findRoutes(routes, point);

    return 0;
}
