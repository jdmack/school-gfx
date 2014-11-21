#ifndef CSE167_MODEL_H_
#define CSE167_MODEL_H_

#include <vector>
#include "vector3.h"
#include "object.h"
#include "triangle.h"

class Model : public Object
{
    private:
        std::vector<Vector3> vertices_;
        std::vector<Vector3> normals_;
        std::vector<Triangle> faces_;

    public:

        Model();
        Model(std::string filename);

        std::vector<Vector3> & vertices() { return vertices_; }
        std::vector<Vector3> & normals() { return normals_; }

        void display(Camera camera = Camera());
        void update(int ticks);
        void reset();

        void parse(std::string filename);
};

#endif

