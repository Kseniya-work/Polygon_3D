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

#include <source/polygon_3D/detail/point.h>
#include <source/polygon_3D/detail/vector.h>


namespace geometry {

/**
 * @struct projection
 * Structure storing a projection data.
 */
struct projection {
    /**
     * @brief Default constructor.
     *  Construct a trivial projection.
     */
    projection(void) 
    : m_num_edge(0), m_param(0.0), m_point(point())
    {}

    /**
     * @brief Сonstructor.
     * Construct a projection with given parameters.
     *
     * @param num_edge Edge number with a projection
     * @param param Parameter of a projection
     * @param point Projection point
     */ 
    projection(const std::size_t& num_edge,
               const double& param,
               const point& point)
    : m_num_edge(num_edge), m_param(param), m_point(point)
    {}

    std::size_t m_num_edge;
    double m_param;
    point m_point;
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
        * @param ipoint Projected point
        * @return Function exit status
        */
        bool calc_projections(const point& ipoint);

       /**
        * @brief Show results of projections calculation.
        * Output calculation results to the console.
        */
        const void show_results();

    private:
        std::vector<point> m_points;
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
        * @param ipoint Projected point
        * @return Projection onto a current edge
        */
        const projection get_projection_for_edge(const std::size_t& i,
                                                 const point& ipoint);
};

}  // namespace geometry

#include <source/polygon_3D/detail/polygon_3D.cpp>
