#include <iostream>
#include <vector>
#include <string>


void draw() {
	int nrows = 15;
	int ncols = 60;
	int x, y;
	std::cout << "|";
	for (x = 0; x < ncols; x++) {
		std::cout << "-";
	}
	std::cout << "|" << std::endl;
	for (x = 0; x < nrows; x++) {
		std::cout << "|";
		for (y = 0; y < ncols; y++) {
			std::cout << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "|";
	for (x = 0; x < ncols; x++) {
		std::cout << "-";
	}
	std::cout << "|" << std::endl;
}


int main() {
	draw();
	return 0;
}
