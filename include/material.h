#ifndef CSE167_MATERIAL_H_
#define CSE167_MATERIAL_H_

class Material
{

    private:
        float ambient_[4];
        float diffuse_[4];
        float specular_[4];
        float shininess_[1];
        float emission_[4];

    public:
        Material();

        // accessors
        float * ambient() { return ambient_; }
        float * diffuse() { return diffuse_; }
        float * specular() { return specular_; }
        float * emission() { return emission_; }
        float * shininess() { return shininess_; }

        // mutators
        void set_ambient(float a, float b, float c, float d);
        void set_diffuse(float a, float b, float c, float d);
        void set_specular(float a, float b, float c, float d);
        void set_shininess(float a);
        void set_emission(float a, float b, float c, float d);

        void set_ambient(float * ambient);
        void set_diffuse(float * diffuse);
        void set_specular(float * specular);
        void set_shininess(float * shininess);
        void set_emission(float * emission);

        void enable();
};


#endif
