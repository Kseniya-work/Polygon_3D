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


namespace geometry {

class point {
    public:
        /**
         * @brief Default constructor.
         *  Construct a trivial point.
         */
        point(void) 
        : m_x(0.0), m_y(0.0), m_z(0.0)
        {}

        /**
         * @brief Сonstructor.
         * Construct a point with given coordinates.
         *
         * @param x x-coordinate of a point
         * @param y y-coordinate of a point
         * @param z z-coordinate of a point
         */ 
        point(const double& x,
              const double& y,
              const double& z)
        : m_x(x), m_y(y), m_z(z)
        {}

        const double get_x() {
            return m_x;
        }

        const double get_y() {
            return m_y;
        }

        const double get_z() {
            return m_z;
        }

        friend bool operator==(const point& left, const point& right);

    private:
        double m_x;
        double m_y;
        double m_z;
};

bool operator==(const point& left, const point& right) {
    return left.m_x == right.m_x &&
           left.m_y == right.m_y &&
           left.m_z == right.m_z;
}

class vector {
    public:
        /**
         * @brief Default constructor.
         *  Construct a trivial vector.
         */
        vector(void) 
        : m_front_point(point(0.0, 0.0, 0.0)),
          m_back_point(point(0.0, 0.0, 0.0))
        {}

        /**
         * @brief Сonstructor.
         * Construct a vector with given points.
         *
         * @param front_point front point of a vector
         * @param back_point back point of a vector
         */ 
        vector(const point& front_point,
               const point& back_point)
        : m_front_point(front_point),
          m_back_point(back_point)
        {
            m_x = this->dir_x();
            m_y = this->dir_y();
            m_z = this->dir_z();
            m_mod = this->mod();
        }

        const point get_front_point() {
            return m_front_point;
        }

        const point get_back_point() {
            return m_back_point;
        }

        const double get_x() {
            return m_x;
        }

        const double get_y() {
            return m_y;
        }

        const double get_z() {
            return m_z;
        }

        const double get_mod() {
            return m_mod;
        }

        const std::pair<double, point> scal_proj(const vector& ivec) {
            double lambda = this->prod(ivec) / m_mod;
            point proj_point(m_front_point.get_x() + lambda * m_x,
                             m_front_point.get_y() + lambda * m_y,
                             m_front_point.get_z() + lambda * m_z);

            return std::make_pair(lambda, proj_point);
        }

        const double prod(const vector& ivec) {
            return ivec.m_x * m_x
                   + ivec.m_y * m_y
                   + ivec.m_z * m_z;
        }

    private:
        double dir_x() {
            return m_back_point.get_x() - m_front_point.get_x();
        }

        double dir_y() {
            return m_back_point.get_y() - m_front_point.get_y();
        }

        double dir_z() {
            return m_back_point.get_z() - m_front_point.get_z();
        }

        double mod() {
            return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
        }

        point m_front_point;
        point m_back_point;
        double m_x;
        double m_y;
        double m_z;
        double m_mod;
};

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

#include <source/polygon_3D/polygon_3D.cpp>
