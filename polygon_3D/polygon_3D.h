#pragma once 

#include <iostream>
#include <sstream>
#include <vector>
#include <exception>
#include <cmath>
#include <algorithm>


namespace polygon {

struct projection
{
    projection(void) 
    : m_num_edge(0), m_param(0.0), m_x(0.0), m_y(0.0), m_z(0.0)
    {}

    projection(std::size_t num_edge,
               double param,
               double x,
               double y,
               double z)
    : m_num_edge(num_edge), m_param(param), m_x(x), m_y(y), m_z(z)
    {}

    std::size_t m_num_edge;
    double m_param;
    double m_x;
    double m_y;
    double m_z;
};

class Polygon_3D { //TODO descriptions
    public:
        bool parse(std::istream& is);
        bool calc_projections(const double& ix,
                              const double& iy,
                              const double& iz);
        const projection get_projection_for_edge(const std::size_t& i,
                                                 const double& ix,
                                                 const double& iy,
                                                 const double& iz);
        const std::size_t get_num_projections();
        const std::vector<projection> get_proj_vec();
        const void show_results();

    private:
        std::vector<double> m_x;
        std::vector<double> m_y;
        std::vector<double> m_z;
        std::vector<std::size_t> m_edges;
        bool m_is_closed = false;

        std::size_t m_num_projections = 0;
        std::vector<projection> m_proj_vec;

        const bool check_closed();
};

}  // namespace polygon

#include <source/polygon_3D/polygon_3D.cpp>
