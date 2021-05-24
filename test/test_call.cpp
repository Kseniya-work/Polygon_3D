#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include <source/polygon_3D/polygon_3D.h>


int main() {
    std::string input_filename = "source/test/data/coord.txt";
    std::ifstream is(input_filename); 
    
    if (!is) {
        std::ostringstream oss;
        oss << "Could not open file \"" << input_filename << "\"";
        throw std::runtime_error(oss.str());  
    }

    std::string ix_str = "", iy_str = "", iz_str = "";
    std::cout << "Please enter a point to calculate projection." << std::endl;
    std::cout << "x: ";
    std::cin >> ix_str;
    std::cout << "y: ";
    std::cin >> iy_str;
    std::cout << "z: ";
    std::cin >> iz_str;

    double ix = 0.0, iy = 0.0, iz = 0.0;
    try {
        ix = std::stod(ix_str);
    }
    catch (const std::exception& e) {
		throw std::runtime_error(
			std::string("input value of coordanate x is invalid: ") + e.what()
		);
	}
    try {
        iy = std::stod(iy_str);
    }
    catch (const std::exception& e) {
		throw std::runtime_error(
			std::string("input value of coordanate y is invalid: ") + e.what()
		);
	}
    try {
        iz = std::stod(iz_str);
    }
    catch (const std::exception& e) {
		throw std::runtime_error(
			std::string("input value of coordanate z is invalid: ") + e.what()
		);
	}

    polygon::Polygon_3D poly;
    poly.parse(is);
    poly.calc_projections(ix, iy, iz);
    poly.show_results();

    return 0;
}