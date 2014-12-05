#ifndef CSE167_MODEL_H_
#define CSE167_MODEL_H_

#include "glee.h"
#include "shader.h"
#include <vector>
#include "vector3.h"
#include "object.h"
#include "triangle.h"
#include "color.h"

class Model : public Object
{
    private:
        std::vector<Vector3> vertices_;
        std::vector<Vector3> normals_;
        std::vector<Triangle> faces_;
        std::vector<Color> colors_;

        Vector3 largest_x_;
        Vector3 largest_y_;
        Vector3 largest_z_;
        Vector3 smallest_x_;
        Vector3 smallest_y_;
        Vector3 smallest_z_;

        Shader shader_;

        Vector3 center_;
    public:

        Model();
        Model(std::string filename);

        std::vector<Vector3> & vertices() { return vertices_; }
        std::vector<Vector3> & normals() { return normals_; }
        std::vector<Triangle> & faces() { return faces_; }
        std::vector<Color> & colors() { return colors_; }

        Shader & shader() { return shader_; }

        void set_shader(Shader shader) { shader_ = shader; }

        void display(Camera camera = Camera());
        void update(int ticks);
        void reset();

        void parse(std::string filename);

        void calculate_dim();
        void calculate_scale();

        static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
        static std::vector<std::string> split(const std::string &s, char delim);
};

#endif

