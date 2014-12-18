#ifndef CSE167_TRIANGLE_H_
#define CSE167_TRIANGLE_H_

#include "vector3.h"
#include "color.h"

class Triangle
{
    private:
        Vector3 vertex1_, vertex2_, vertex3_;
        Vector3 normal1_, normal2_, normal3_;
        Vector3 texel1_, texel2_, texel3_;
        Color color1_, color2_, color3_;
        std::string texture_key_;
    
    public:
        Triangle();
        Triangle(Vector3 v1, Vector3 n1, Color c1, Vector3 v2, Vector3 n2, Color c2, Vector3 v3, Vector3 n3, Color c3);

        Vector3 & vertex1() { return vertex1_; }
        Vector3 & vertex2() { return vertex2_; }
        Vector3 & vertex3() { return vertex3_; }

        Vector3 & normal1() { return normal1_; }
        Vector3 & normal2() { return normal2_; }
        Vector3 & normal3() { return normal3_; }

        Vector3 & texel1() { return texel1_; }
        Vector3 & texel2() { return texel2_; }
        Vector3 & texel3() { return texel3_; }

        Color & color1() { return color1_; }
        Color & color2() { return color2_; }
        Color & color3() { return color3_; }

        std::string texture_key() { return texture_key_; }

        void set_vertex1(Vector3 v) { vertex1_ = v; }
        void set_vertex2(Vector3 v) { vertex2_ = v; }
        void set_vertex3(Vector3 v) { vertex3_ = v; }

        void set_normal1(Vector3 n) { normal1_ = n; }
        void set_normal2(Vector3 n) { normal2_ = n; }
        void set_normal3(Vector3 n) { normal3_ = n; }

        void set_texel1(Vector3 t) { texel1_ = t; }
        void set_texel2(Vector3 t) { texel2_ = t; }
        void set_texel3(Vector3 t) { texel3_ = t; }

        void set_color1(Color c) { color1_ = c; }
        void set_color2(Color c) { color2_ = c; }
        void set_color3(Color c) { color3_ = c; }

        void set_texture_key(std::string key) { texture_key_ = key; }
};


#endif
