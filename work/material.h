#ifndef CSE167_MATERIAL_H_
#define CSE167_MATERIAL_H_

#include "struct.h"

class Material
{

    private:
        float4 ambient_;
        float4 diffuse_;
        float4 specular_;
        float1 shininess_;
        float4 emission_;

    public:
        Material();
        Material(float4 ambient, float4 diffuse, float4 specular, float1 shininess, float4 emission);

        // accessors
        float4 ambient() { return ambient_; }
        float4 diffuse() { return diffuse_; }
        float4 specular() { return specular_; }
        float4 emission() { return emission_; }
        float1 shininess() { return shininess_; }

        // mutators
        void set_ambient(float4 ambient) { ambient_ = ambient; }
        void set_diffuse(float4 diffuse) { diffuse_ = diffuse; }
        void set_specular(float4 specular) { specular_ = specular; }
        void set_shininess(float1 shininess) { shininess_ = shininess; }
        void set_emission(float4 emission) { emission_ = emission; }

        void render();
};


#endif
