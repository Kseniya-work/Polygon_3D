/******************************************************************************
    * File: polygon_3D.h
    * Description: Manipulation of polygon in 3D space.
    * Created: 24 may 2021
    * Author: Kseniya Nosulko
    * Email: knosulko@gmail.com

******************************************************************************/
#pragma once 

#include <iostream>
#include <sstream>
#include <vector>
#include <exception>
#include <cmath>
#include <algorithm>


namespace polygon {

/**
 * @struct projection
 * Structure storing a projection data.
 */
struct projection
{
    /**
     * @brief Default constructor.
     *  Construct a trivial projection.
     */
    projection(void) 
    : m_num_edge(0), m_param(0.0), m_x(0.0), m_y(0.0), m_z(0.0)
    {}

    /**
     * @brief Сonstructor.
     * Construct a projection with given parameters.
     *
     * @param num_edge Edge number with a projection
     * @param param Parameter of a projection
     * @param x x-coordinate of a projection point
     * @param y y-coordinate of a projection point
     * @param z z-coordinate of a projection point
     */ 
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

/**
 * @class Polygon_3D
 * Class provides operations with polygon in 3D space.
 * @see projection
 */
class Polygon_3D {
    public:
       /**
        * Parse input stream content.
        *
        * @param is Input stream with coordinates of vertices
        * @return Function exit status
        */
        bool parse(std::istream& is);

       /**
        * Calculate projections of a projected point onto the polygon.
        *
        * @param ix x-coordinate of a projected point
        * @param iy y-coordinate of a projected point
        * @param iz z-coordinate of a projected point
        * @return Function exit status
        */
        bool calc_projections(const double& ix,
                              const double& iy,
                              const double& iz);

       /**
        * @brief Show results of projections calculation.
        * Output calculation results to the console.
        */
        const void show_results();

    private:
        std::vector<double> m_x;
        std::vector<double> m_y;
        std::vector<double> m_z;
        std::vector<std::size_t> m_edges;
        bool m_is_closed = false;
        std::size_t m_num_projections = 0;
        std::vector<projection> m_proj_vec;

       /**
        * Check if the polygon is closed.
        *
        * @return Function exit status
        */
        const bool check_closed();

        /**
        * Get projection of a projected point onto a current edge.
        *
        * @param i Index of point in polygon
        * @param ix x-coordinate of a projected point
        * @param iy y-coordinate of a projected point
        * @param iz z-coordinate of a projected point
        * @return Projection onto a current edge
        */
        const projection get_projection_for_edge(const std::size_t& i,
                                                 const double& ix,
                                                 const double& iy,
                                                 const double& iz);
};

}  // namespace polygon

#include <source/polygon_3D/polygon_3D.cpp>
