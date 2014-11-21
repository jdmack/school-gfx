#ifndef CSE167_LIGHT_H_
#define CSE167_LIGHT_H_

#include "struct.h"

class Light
{
    private:
        int number_;
        float4 ambient_;
        float4 diffuse_;
        float4 specular_;
        float4 position_;

    public:
        Light();
        Light(int number);
        void set_ambient(float4 am);
        void set_diffuse(float4 di);
        void set_specular(float4 sp);
        void set_position(float4 po);

        void render();
};


#endif
