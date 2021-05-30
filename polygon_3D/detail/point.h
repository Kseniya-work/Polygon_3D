namespace geometry {

/**
 * @class point
 * Class provides operations with point in 3D space.
 */
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

       /**
        * Get x-coordinate of a point.
        *
        * @return x-coordinate of a point
        */
        const double get_x() {
            return m_x;
        }

       /**
        * Get y-coordinate of a point.
        *
        * @return y-coordinate of a point
        */
        const double get_y() {
            return m_y;
        }

       /**
        * Get z-coordinate of a point.
        *
        * @return z-coordinate of a point
        */
        const double get_z() {
            return m_z;
        }

        friend bool operator==(const point& left, const point& right);

    private:
        double m_x;
        double m_y;
        double m_z;
};

/**
* Compare the equality of two points.
*
* @return True if equal, else false
*/
bool operator==(const point& left, const point& right) {
    return left.m_x == right.m_x &&
           left.m_y == right.m_y &&
           left.m_z == right.m_z;
}

}  // namespace geometry
