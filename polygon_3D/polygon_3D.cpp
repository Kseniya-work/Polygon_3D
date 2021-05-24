namespace polygon {

bool Polygon_3D::parse(std::istream& is) {
    std::string line = "";
    std::size_t current_point_num = 0;  // for writing edges

    std::getline(is, line, '\n');  // read line 0: "x   y   z"
    while(std::getline(is, line, '\n')) {
        std::istringstream iss(line);
        double _x = 0.0, _y = 0.0, _z = 0.0;  // if some coordinate of a point is missing, it will be replaced by zero
        iss >> _x >> _y >> _z;

        m_x.push_back(_x);
        m_y.push_back(_y);
        m_z.push_back(_z);

        m_edges.push_back(current_point_num++);
		m_edges.push_back(current_point_num);
    }

    if (m_x.size() == 0 && m_y.size() == 0 && m_z.size() == 0) {
        throw std::runtime_error("file with coordinates is empty.");
    }

    if (this->check_closed()) {
        m_edges.back() = m_edges.front();
        m_is_closed = true;
    }
    else {
        m_edges.pop_back();
        m_edges.pop_back();
    }

    return true;
}

const bool Polygon_3D::check_closed() {
    return (m_x.front() == m_x.back()) &&
           (m_y.front() == m_y.back()) &&
           (m_z.front() == m_z.back());
}

bool Polygon_3D::calc_projections(const double& ix,
                                  const double& iy,
                                  const double& iz)
{
    double cur_dist;  // distance from point (ix, iy, iz) to the current edge
    double min_dist;  // min distance to edges
    std::vector<std::size_t> min_dist_indices;  // indices of edges with minimal distance
    std::vector<projection> all_proj;  // vector of projections to each edge

    // calculate the projection on first edge
    std::size_t i = 0;
    projection cur_proj = this->get_projection_for_edge(i, ix, iy, iz);
    all_proj.push_back(cur_proj);
    min_dist = sqrt(pow(ix - cur_proj.m_x, 2) + pow(iy - cur_proj.m_y, 2) + pow(iz - cur_proj.m_z, 2));
    min_dist_indices.push_back(i);

    for (std::size_t i = 2; i < m_edges.size(); i += 2) {
        projection cur_proj = this->get_projection_for_edge(i, ix, iy, iz);
        all_proj.push_back(cur_proj);
        cur_dist = sqrt(pow(ix - cur_proj.m_x, 2) + pow(iy - cur_proj.m_y, 2) + pow(iz - cur_proj.m_z, 2));

        if (cur_dist < min_dist) {
            min_dist = cur_dist;
            min_dist_indices.clear();
            min_dist_indices.push_back(i / 2);
        }
        else if (cur_dist == min_dist) {
            min_dist_indices.push_back(i / 2);
        }
    }

    if (m_is_closed) {
        all_proj.pop_back();
        if (min_dist_indices.back() == m_x.size() - 1) {
            min_dist_indices.pop_back();
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
                                                     const double& ix,
                                                     const double& iy,
                                                     const double& iz)
{
    double lambda;
    double proj_x;
    double proj_y;
    double proj_z;

    std::size_t num_point_left = m_edges[i];
    std::size_t num_point_right = m_edges[i + 1];

    // coordinates of the left point of the edge
    double xl = m_x[num_point_left];
    double yl = m_y[num_point_left];
    double zl = m_z[num_point_left];

    // coordinates of the right point of the edge
    double xr = m_x[num_point_right];
    double yr = m_y[num_point_right];
    double zr = m_z[num_point_right];

    if (xl == xr &&
        yl == yr &&
        zl == zr)  // singular edge
    {
        lambda = 0;
        proj_x = xl;
        proj_y = yl;
        proj_z = zl;
    }
    else {
        // direction vector of edge
        double dx_edge = xr - xl;
        double dy_edge = yr - yl;
        double dz_edge = zr - zl;

        // direction vector of line through points (ix, iy, iz) and (xl, yl, zl)
        double dx_i = ix - xl;
        double dy_i = iy - yl;
        double dz_i = iz - zl;

        lambda = (dx_edge * dx_i + dy_edge * dy_i + dz_edge * dz_i) / 
                 (pow(dx_edge, 2) + pow(dy_edge, 2) + pow(dz_edge, 2));

        // coordinate of projection point
        proj_x = dx_edge * lambda + xl;
        proj_y = dy_edge * lambda + yl;
        proj_z = dz_edge * lambda + zl;

        if (lambda < 0) {
            lambda = 0.0;
            proj_x = xl;
            proj_y = yl;
            proj_z = zl;
        }
        else if (lambda > 1) {
            lambda = 1.0;
            proj_x = xr;
            proj_y = yr;
            proj_z = zr;
        }
    }

    projection proj(i / 2, lambda, proj_x, proj_y, proj_z);

    return proj;
}

const std::size_t Polygon_3D::get_num_projections() {
    return m_num_projections;
}

const std::vector<projection> Polygon_3D::get_proj_vec() {
    return m_proj_vec;
}

const void Polygon_3D::show_results() {
    std::ostringstream oss;
    oss << "number of solutions: " << m_num_projections << std::endl;
    std::for_each(m_proj_vec.begin(),
                  m_proj_vec.end(),
                  [&oss](const auto& proj) {
                      oss << "segment number: " << proj.m_num_edge << ", " <<
                             "projection parameter: " << proj.m_param << ", " <<
                             "point of projection: (" << proj.m_x << ", " <<
                                                         proj.m_y << ", " <<
                                                         proj.m_z << ")" << std::endl; 
                  }
    );
    std::cout << oss.str(); 
}

} // namespace polygon