#include <cmath>
#include <iostream>

void f(double a, double b) {
	double x = 1.0;

	for (int i = 0; i <= 20; ++i) {
		double y;

		if (x < b) {
			y = sin(abs(a * x + pow(b, a)));
		}
		else {
			y = cos(abs(a * x - pow(b, a)));
		}

		std::cout << "x = " << x << ", y = " << y << "\n";

		x += 0.1;
	}
}

int main() {
	f(1.5, 2.0);
}
