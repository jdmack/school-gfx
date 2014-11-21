#ifndef CSE167_LIGHT_H_
#define CSE167_LIGHT_H_

class Light
{
    private:
        int number_;
        bool enabled_;
        float ambient_[4];
        float diffuse_[4];
        float specular_[4];
        float position_[4];

    public:
        Light();
        Light(int number);

        // accessors
        bool enabled() { return enabled_; }

        // mutators
        void set_ambient(float a, float b, float c, float d);
        void set_diffuse(float a, float b, float c, float d);
        void set_specular(float a, float b, float c, float d);
        void set_position(float a, float b, float c, float d);

        void enable();
        void disable();
};


#endif
