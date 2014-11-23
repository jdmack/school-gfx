#ifndef CSE167_LIGHT_H_
#define CSE167_LIGHT_H_

class Light
{
    protected:
        int number_;
        bool enabled_;
        float ambient_[4];
        float diffuse_[4];
        float specular_[4];
        float position_[4];
        float constant_atten_[1];
        float linear_atten_[1];
        float quadratic_atten_[1];

    public:
        Light();
        Light(int number);

        // accessors
        bool enabled() { return enabled_; }

        // mutators
        void set_ambient(float a, float b, float c, float d);
        void set_diffuse(float a, float b, float c, float d);
        void set_specular(float a, float b, float c, float d);
        void set_position(float x, float y, float z, float w);
        void set_constant_atten(float constant_atten) { constant_atten_[0] = constant_atten; }
        void set_linear_atten(float linear_atten) { linear_atten_[0] = linear_atten; }
        void set_quadratic_atten(float quadratic_atten) { quadratic_atten_[0] = quadratic_atten; }

        //virtual void set();
        virtual void enable();
        void disable();
};


#endif
