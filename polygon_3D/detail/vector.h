namespace geometry {

/**
 * @class vector
 * Class provides operations with vector in 3D space.
 */
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

        /**
         * Get front point of a vector.
         *
         * @return Front point of a vector
         */
        const point get_front_point() {
            return m_front_point;
        }

        /**
         * Get back point of a vector.
         *
         * @return Back point of a vector
         */
        const point get_back_point() {
            return m_back_point;
        }

        /**
         * Get x-coordinate of a vector.
         *
         * @return x-coordinate of a vector
         */
        const double get_x() {
            return m_x;
        }

        /**
         * Get y-coordinate of a vector.
         *
         * @return y-coordinate of a vector
         */
        const double get_y() {
            return m_y;
        }

        /**
         * Get z-coordinate of a vector.
         *
         * @return z-coordinate of a vector
         */
        const double get_z() {
            return m_z;
        }

        /**
         * Get modulus of a vector.
         *
         * @return Modulus of a vector
         */
        const double get_mod() {
            return m_mod;
        }

        /**
         * Calculate the scalar projection of an input vector to a current one.
         *
         * @return Pair of a projection parameter and a projection point
         */
        const std::pair<double, point> scal_proj(const vector& ivec) {
            double lambda = this->prod(ivec) / m_mod;
            point proj_point(m_front_point.get_x() + lambda * m_x,
                             m_front_point.get_y() + lambda * m_y,
                             m_front_point.get_z() + lambda * m_z);

            return std::make_pair(lambda, proj_point);
        }

        /**
         * Calculate a product of an input vector and a current one.
         *
         * @return Product of vectors
         */
        const double prod(const vector& ivec) {
            return ivec.m_x * m_x
                   + ivec.m_y * m_y
                   + ivec.m_z * m_z;
        }

    private:
        /**
         * Calculate x-coordinate of a vector.
         *
         * @return x-coordinate of a vector
         */
        double dir_x() {
            return m_back_point.get_x() - m_front_point.get_x();
        }

        /**
         * Calculate y-coordinate of a vector.
         *
         * @return y-coordinate of a vector
         */
        double dir_y() {
            return m_back_point.get_y() - m_front_point.get_y();
        }

        /**
         * Calculate z-coordinate of a vector.
         *
         * @return z-coordinate of a vector
         */
        double dir_z() {
            return m_back_point.get_z() - m_front_point.get_z();
        }

        /**
         * Calculate a modulus of a vector.
         *
         * @return Modulus of a vector
         */
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

}  // namespace geometry
