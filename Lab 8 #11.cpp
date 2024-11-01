#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include <cassert>

// Продукт
class Item {
private:
	// Продукт характеризується назвою, кількістю, масою і ціною
	std::string name;
	int quantity;
	double mass;
	double price;

public:
	// 1. Конструктор за замовчуванням
	Item() : name("Unnamed"), quantity(0), mass(0.0), price(0.0) {}

	// 2. Деструктор (порожній, оскільки немає динамічних ресурсів, які вимагатимуть очистки)
	~Item() {}

	// 3. Конструктор з параметрами
	Item(std::string name, int quantity, double mass, double price) :
		name(name), quantity(quantity), mass(mass), price(price) {}

	// 4. Конструктор копіювання
	Item(const Item& item) :
		name(item.name), quantity(item.quantity), mass(item.mass), price(item.price) {}

	// 5. Перевантажена операція присвоєння
	Item& operator=(const Item& item) {
		if (this != &item) {
			name = item.name;
			quantity = item.quantity;
			mass = item.mass;
			price = item.price;
		}
		return *this;
	}

	// 6. Перевантажена операція виведення в потік
	friend std::ostream& operator<<(std::ostream& stream, const Item& item) {
		stream << "Item, named " << item.name << " with quantity of " << item.quantity <<
			"; its mass is " << item.mass << " and price is " << item.price;

		return stream;
	}

	// 7. Перевантажена операція вводу із потоку
	friend std::istream& operator>>(std::istream& stream, Item& item) {
		std::cout << "Enter item name: ";
		stream >> item.name;

		std::cout << "Enter quantity: ";
		stream >> item.quantity;

		std::cout << "Enter mass: ";
		stream >> item.mass;

		std::cout << "Enter price: ";
		stream >> item.price;

		return stream;
	}

	// 8. Перевантажена арифметична операція (множення продуктів)
	Item operator*(int multiplier) const {
		if (multiplier < 0) {
			throw std::invalid_argument("Multiplier cannot be negative.");
		}

		return Item(name, quantity * multiplier, mass, price);
	}

	// 9. Перевантажена логічна операція (порівння продуктів за видом)
	bool operator==(const Item& item) const {
		return name == item.name;
	}

	// 10. Перевантажена операція приведення до типу (отримання кількості)
	operator int() const {
		return quantity;
	}

	// 11. Необхідні методи (getters & setters)
	std::string getName() const { return name; }
	int getQuantity() const { return quantity; }
	double getMass() const { return mass; }
	double getPrice() const { return price; }

	void setName(const std::string& newName) { name = newName; }
	void setQuantity(int newQuantity) { quantity = newQuantity; }
	void setMass(double newMass) { mass = newMass; }
	void setPrice(double newPrice) { price = newPrice; }
};

// Місто
class City {
private:
	// Місто характеризується назвою, областю та населенням
	std::string name;
	std::string region;
	int population;

public:
	// 1. Конструктор за замовчуванням
	City() : name("Unknown"), region("Unknown"), population(0) {}

	// 2. Деструктор (порожній, оскільки немає динамічних ресурсів, які вимагатимуть очистки)
	~City() {}

	// 3. Конструктор з параметрами
	City(const std::string& name, const std::string& region, int population)
		: name(name), region(region), population(population) {}

	// 4. Конструктор копіювання
	City(const City& other)
		: name(other.name), region(other.region), population(other.population) {}

	// 5. Перевантажена операція присвоєння
	City& operator=(const City& city) {
		if (this != &city) {
			name = city.name;
			region = city.region;
			population = city.population;
		}
		return *this;
	}

	// 6. Перевантажена операція виведення в потік
	friend std::ostream& operator<<(std::ostream& stream, const City& city) {
		stream << "City: " << city.name << ", Region: " << city.region << ", Population: " << city.population;
		return stream;
	}

	// 7. Перевантажена операція вводу із потоку
	friend std::istream& operator>>(std::istream& stream, City& city) {
		std::cout << "Enter the name of the city: ";
		stream >> city.name;

		std::cout << "Enter the region of the city: ";
		stream >> city.region;

		std::cout << "Enter the population of the city: ";
		stream >> city.population;

		return stream;
	}

	// 8. Перевантажена арифметична операція (додавання населення; назви "з'єднуються" відповідно)
	City operator+(const City& city) const {
		return City(name + " & " + city.name, region, population + city.population);
	}

	// 9. Перевантажена логічна операція (порівняння за населенням)
	bool operator==(const City& city) const {
		return population == city.population;
	}

	// 10. Перевантажена операція приведення до типу (отримання населення)
	operator int() const {
		return population;
	}

	// 11. Необхідні методи (getters & setters)
	void setName(const std::string& newName) { name = newName; }
	void setRegion(const std::string& newRegion) { region = newRegion; }
	void setPopulation(int newPopulation) { population = newPopulation; }

	std::string getName() const { return name; }
	std::string getRegion() const { return region; }
	int getPopulation() const { return population; }
};

// Магазин
class Shop {
private:
	// Магазин характеризується назвою та списком продуктів
	std::string name;
	std::vector<Item> items;
	/* 
	*   оскільки задачами є також дізнатися назву міста та назву області для
	*   даного магазину, то, на мою думку, доречним способом пов'язати ці об'єкти
	*   буде використання спільного вказівника на місто (тому що одному місту
	*   можуть належати багато магазинів)
	*/
	std::shared_ptr<City> city; 
public:
	// 1. Конструктор за замовчуванням
	Shop() : name("Unnamed"), city(std::make_shared<City>()) {}

	// 2. Деструктор (порожній, оскільки немає динамічних ресурсів, які вимагатимуть очистки)
	~Shop() {}

	// 3. Конструктор з параметрами
	Shop(std::string name, std::shared_ptr<City> city) : name(name), city(city) {}

	// 4. Конструктор копіювання
	Shop(const Shop& shop) : name(shop.name), items(shop.items), city(shop.city) {}

	// 5. Перевантажена операція присвоєння
	Shop& operator=(const Shop& shop) {
		if (this != &shop) {
			name = shop.name;
			items = shop.items;
			city = shop.city;
		}
		return *this;
	}

	// 6. Перевантажена операція виведення в потік
	friend std::ostream& operator<<(std::ostream& stream, const Shop& shop) {
		if (!shop.city) {
			throw std::runtime_error("The city cannot be NULL.");
		}

		stream << "Shop name: " << shop.name << ", city: " << shop.city->getName() << ", items:\n";
		for (const Item& item : shop.items) {
			std::cout << "Name = " << item.getName() << ", mass = " << item.getMass()
				<< ", quantity = " << item.getQuantity() << ", price = " << item.getPrice();
		}

		return stream;
	}

	// 7. Перевантажена операція вводу із потоку
	friend std::istream& operator>>(std::istream& stream, Shop& shop) {
		std::cout << "Enter shop name: ";
		stream >> shop.name;

		int totalQuantity = 0;
		std::cout << "Enter the quantity of items: ";
		stream >> totalQuantity;

		shop.items.clear();
		for (int i = 0; i < totalQuantity; ++i) {
			Item item;
			stream >> item;
			shop.items.push_back(item);
		}

		/*
		* Прив'язка до міста нехай буде здійснюватись ззовні,
		* оскільки "створення міста всередині магазину" не має ієрархічного смислу
		*/

		return stream;
	}

	// 8. Перевантажена арифметична операція (унарний плюс, отримання повної вартості товарів)
	double operator+() const {
		double cumulative = 0.0;
		for (const Item& item : items) {
			cumulative += item.getPrice() * item.getQuantity();
		}
		return cumulative;
	}

	// 9. Перевантажена логічна операція (порівняння магазинів за назвою)
	bool operator==(const Shop& shop) const {
		return name == shop.name;
	}

	// 10. Перевантаження операція приведення до типу (булевий тип, перевірка кількості товарів)
	explicit operator bool() const {
		return !items.empty();  // Returns true if the shop has items
	}

	// 11. Необхідні методи

	// 11.1. Отримання міста
	std::string getCityName() const {
		if (!city) { throw std::runtime_error("The city cannot be NULL."); }
		return city->getName();
	}

	// 11.2. Отримання області
	std::string getRegionName() const {
		if (!city) { throw std::runtime_error("The city cannot be NULL."); }
		return city->getRegion();
	}

	// 11.3. Перевірка належності до області
	bool belongsToRegion(const std::string& region) const {
		if (!city) { throw std::runtime_error("The city cannot be NULL."); }
		return city->getRegion() == region;
	}

	// 11.4 Визначення середньої маси всіх продуктів
	double averageWeight() const {
		int total = totalQuantity();
		if (total == 0) {
			return 0;
		}

		double totalMass = 0;
		for (const Item& item : items) {
			totalMass += item.getQuantity() * item.getMass();
		}

		return totalMass / total;
	}

	// 11.5. Додання продукту
	void addItem(const Item& item) {
		items.push_back(item);
	}

	// 11.6. Видалення товару за назвою
	void removeItem(const std::string& itemName) {
		items.erase(std::remove_if(items.begin(), items.end(),
			[&itemName](const Item& item) { return item.getName() == itemName; }), items.end());
	}

	// 11.7. Перевірка існування елементу за назвою
	bool itemExists(const std::string& itemName) const {
		return std::any_of(items.begin(), items.end(),
			[&itemName](const Item& item) { return item.getName() == itemName; });
	}

	// 11.8. Пошук сумарної кількості усіх продуктів
	int totalQuantity() const {
		int total = 0;
		for (const Item& item : items) {
			total += item.getQuantity();
		}

		return total;
	}
};

void testItem() {
	// Тестування конструктора за замовчуванням
	Item defaultItem;
	assert(defaultItem.getName() == "Unnamed");
	assert(defaultItem.getQuantity() == 0);
	assert(defaultItem.getMass() == 0.0);
	assert(defaultItem.getPrice() == 0.0);

	// Тестування конструктора з параметрами
	Item apple("Apple", 10, 0.25, 3.5);
	assert(apple.getName() == "Apple");
	assert(apple.getQuantity() == 10);
	assert(apple.getMass() == 0.25);
	assert(apple.getPrice() == 3.5);

	// Тестування копіювання
	Item copiedItem = apple;
	assert(copiedItem.getName() == apple.getName());
	assert(copiedItem.getQuantity() == apple.getQuantity());

	// Тестування оператора присвоєння
	Item assignedItem;
	assignedItem = apple;
	assert(assignedItem.getName() == apple.getName());

	// Тестування введення/виведення (перевірка наявності)
	std::ostringstream out;
	out << apple;
	assert(out.str() == "Item, named Apple with quantity of 10; its mass is 0.25 and price is 3.5");

	// Тестування множення
	Item multipliedItem = apple * 2;
	assert(multipliedItem.getQuantity() == 20);
	assert(multipliedItem.getMass() == 0.25); // маса не повинна змінюватись
	assert(multipliedItem.getPrice() == 3.5); // ціна не повинна змінюватись

	// Тестування порівняння
	Item anotherApple("Apple", 5, 0.25, 3.5);
	assert(apple == anotherApple); // порівняння за назвою

	// Тестування приведення до типу
	int quantity = apple;
	assert(quantity == 10);
}

void testCity() {
	// Тестування конструктора за замовчуванням
	City defaultCity;
	assert(defaultCity.getName() == "Unknown");
	assert(defaultCity.getRegion() == "Unknown");
	assert(defaultCity.getPopulation() == 0);

	// Тестування конструктора з параметрами
	City kyiv("Kyiv", "Kyiv Region", 2950000);
	assert(kyiv.getName() == "Kyiv");
	assert(kyiv.getRegion() == "Kyiv Region");
	assert(kyiv.getPopulation() == 2950000);

	// Тестування копіювання
	City copiedCity = kyiv;
	assert(copiedCity.getName() == kyiv.getName());
	assert(copiedCity.getRegion() == kyiv.getRegion());
	assert(copiedCity.getPopulation() == kyiv.getPopulation());

	// Тестування оператора присвоєння
	City assignedCity;
	assignedCity = kyiv;
	assert(assignedCity.getName() == kyiv.getName());

	// Тестування введення/виведення
	std::ostringstream out;
	out << kyiv;
	assert(out.str() == "City: Kyiv, Region: Kyiv Region, Population: 2950000");

	// Тестування додавання міст
	City lviv("Lviv", "Lviv Region", 720000);
	City combinedCity = kyiv + lviv;
	assert(combinedCity.getName() == "Kyiv & Lviv");
	assert(combinedCity.getPopulation() == 3670000);

	// Тестування порівняння
	City anotherCity("Odesa", "Odesa Region", 1000000);
	assert(!(kyiv == anotherCity)); // різні населення

	// Тестування приведення до типу
	int population = kyiv;
	assert(population == 2950000);
}

void testShop() {
	// Тестування конструктора за замовчуванням
	Shop defaultShop;
	assert(defaultShop.totalQuantity() == 0);
	assert(defaultShop.itemExists("SomeItem") == false);

	// Тестування конструктора з параметрами
	std::shared_ptr<City> city = std::make_shared<City>("Kyiv", "Kyiv Region", 2950000);
	Shop myShop("My Shop", city);
	assert(myShop.totalQuantity() == 0);

	// Тестування додавання товару
	Item apple("Apple", 10, 0.25, 5);
	myShop.addItem(apple);
	assert(myShop.totalQuantity() == 10);
	assert(myShop.itemExists("Apple") == true);

	// Тестування видалення товару
	myShop.removeItem("Apple");
	assert(myShop.totalQuantity() == 0);
	assert(myShop.itemExists("Apple") == false);

	// Тестування додавання кількох товарів
	Item banana("Banana", 5, 0.5, 8);
	Item orange("Orange", 3, 0.35, 12);
	myShop.addItem(banana);
	myShop.addItem(orange);
	assert(myShop.totalQuantity() == 8);

	// Тестування сумарної вартості товарів
	double totalValue = +myShop;
	assert(totalValue == 76.0); // 5 * 8 + 12 * 3 = 76

	// Тестування наявності товару
	assert(myShop.itemExists("Banana") == true);
	assert(myShop.itemExists("Orange") == true);
	assert(myShop.itemExists("Apple") == false);

	// Тестування видалення з порожнього магазину
	myShop.removeItem("Apple"); // Не повинно викликати помилку
}

int main() {
	testItem();
	testCity();
	testShop();

	return 0;
}
