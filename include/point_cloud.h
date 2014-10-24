#ifndef CSE167_POINT_CLOUD_H_
#define CSE167_POINT_CLOUD_H_

#include <string>
#include <vector>
#include "vector3.h"
#include "object.h"
#include "camera.h"

class PointCloud : public Object
{
protected:
    std::vector<Vector3> points_;
    std::vector<Vector3> normals_;

    Vector3 largest_x_;
    Vector3 largest_y_;
    Vector3 largest_z_;
    Vector3 smallest_x_;
    Vector3 smallest_y_;
    Vector3 smallest_z_;

    Vector3 center_;

public:
    // constructors
    PointCloud();
    PointCloud(std::string);

    std::vector<Vector3> & points() { return points_; }
    std::vector<Vector3> & normals() { return normals_; }

    void display(Camera camera = Camera());
    void update(int ticks);
    void reset();

    void parse(std::string filename);
    void calculate_dim();

    void calculate_scale();


};

#endif
