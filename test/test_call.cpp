#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <array>


#include <source/polygon_3D/polygon_3D.h>

/**
 * @brief Entry point.
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */
int main() {
    std::string input_filename = "source/test/data/coord.txt";
    std::ifstream is(input_filename); 
    
    if (!is) {
        std::ostringstream oss;
        oss << "Could not open file \"" << input_filename << "\"";
        throw std::runtime_error(oss.str());  
    }

    std::array<double, 3> icoordinates = {0.0, 0.0, 0.0}; // x, y, z
    std::string coordinates_name = "xyz";
    std::cout << "Please enter a point to calculate projection." << std::endl;
    for(int i = 0; i < coordinates_name.length(); i++){
        std::cout << coordinates_name[i] << ": ";
        std::string icoordinate_str = "";
        std::cin >> icoordinate_str;
        try {
            icoordinates[i] = std::stod(icoordinate_str);
        }
        catch (const std::exception& e) {
            throw std::runtime_error(
                std::string("input value of coordanate ")
                + coordinates_name[i]
                + std::string(" is invalid: ")
                + e.what()
            );
        }
    }

    polygon::Polygon_3D poly;
    poly.parse(is);
    poly.calc_projections(icoordinates[0], 
                          icoordinates[1], 
                          icoordinates[2]);
    poly.show_results();

    return 0;
}