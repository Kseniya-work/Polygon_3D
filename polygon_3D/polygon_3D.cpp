/******************************************************************************
    * File: polygon_3D.cpp
    * Description: Manipulation of polygon in 3D space.
    * Created: 24 may 2021
    * Author: Kseniya Nosulko
    * Email: knosulko@gmail.com

******************************************************************************/
namespace geometry {

bool Polygon_3D::parse(std::istream& is) {
    std::string line = "";
    std::size_t current_point_num = 0;  // for writing edges

    std::getline(is, line, '\n');  // read line 0: "x   y   z"
    while(std::getline(is, line, '\n')) {
        std::istringstream iss(line);
        double _x = 0.0, _y = 0.0, _z = 0.0;  // if some coordinate of a point is missing, it will be replaced by zero
        iss >> _x >> _y >> _z;

        m_points.push_back(point(_x, _y, _z));
    }

    if (m_points.size() == 0) {
        throw std::runtime_error("file with coordinates is empty.");
    }

    m_is_closed = this->check_closed() ? true : false;

    return true;
}

const bool Polygon_3D::check_closed() {
    return m_points.front() == m_points.back();
}

bool Polygon_3D::calc_projections(const point& ipoint)
{
    double cur_dist;  // distance from point (ix, iy, iz) to the current edge
    double min_dist;  // min distance to edges
    std::vector<std::size_t> min_dist_indices;  // indices of edges with minimal distance
    std::vector<projection> all_proj;  // vector of projections to each edge

    // calculate the projection on first edge
    std::size_t i = 0;
    projection cur_proj = this->get_projection_for_edge(i, ipoint);
    all_proj.push_back(cur_proj);
    min_dist = vector(ipoint, cur_proj.m_point).get_mod();
    min_dist_indices.push_back(i);

    for (std::size_t i = 1; i < m_points.size() - 1; i++) {
        projection cur_proj = this->get_projection_for_edge(i, ipoint);
        all_proj.push_back(cur_proj);
        cur_dist = vector(ipoint, cur_proj.m_point).get_mod();

        if (cur_dist < min_dist) {
            min_dist = cur_dist;
            min_dist_indices.clear();
            min_dist_indices.push_back(i);
        }
        else if (cur_dist == min_dist) {
            min_dist_indices.push_back(i);
        }
    }

    std::for_each(min_dist_indices.begin(),
                  min_dist_indices.end(),
                  [this, &all_proj](const auto& i) {
                      m_proj_vec.push_back(all_proj[i]);
                  }
    );

    m_num_projections = m_proj_vec.size();

    return true;
}

const projection Polygon_3D::get_projection_for_edge(const std::size_t& i,
                                                     const point& ipoint)
{
    double lambda;
    point proj_point;

    vector edge(m_points[i], m_points[i + 1]);  // edge vector

    if (edge.get_mod() == 0.0) {  // singular edge
        lambda = 0.0;
        proj_point = edge.get_front_point();
    }
    else {
        vector ivector(m_points[i], ipoint);  // vector of line through points (ix, iy, iz) and (xl, yl, zl)
        std::pair<double, point> scal_proj_data = edge.scal_proj(ivector);  // parametr and projection point
        lambda = scal_proj_data.first;
        proj_point = scal_proj_data.second;
        
        if (lambda < 0) {
            lambda = 0.0;
            proj_point = edge.get_front_point();
        }
        else if (lambda > 1) {
            lambda = 1.0;
            proj_point = edge.get_back_point();
        }
    }

    return projection(i, lambda, proj_point);
}

const void Polygon_3D::show_results() {
    std::ostringstream oss;
    oss << "number of solutions: " << m_num_projections << std::endl;
    std::for_each(m_proj_vec.begin(),
                  m_proj_vec.end(),
                  [&oss](auto& proj) {
                      oss << "segment number: " << proj.m_num_edge << ", " <<
                             "projection parameter: " << proj.m_param << ", " <<
                             "point of projection: (" << proj.m_point.get_x() << ", " <<
                                                         proj.m_point.get_y() << ", " <<
                                                         proj.m_point.get_z() << ")" << std::endl; 
                  }
    );
    std::cout << oss.str(); 
}

} // namespace geometry