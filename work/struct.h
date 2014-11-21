#ifndef CSE167_STRUCT_H_
#define CSE167_STRUCT_H_

struct float1
{
    float val[1];
    float1(float a)
    {
        val[0] = a;
    }

    float1()
    {
        val[0] = 0.0;
    }

    float1(float1 & param)
    {
        val[0] = param.val[0];
    }

    void set(float a)
    {
        val[0] = a;
    }
};

struct float2
{
    float val[2];
    float2(float a, float b)
    {
        val[0] = a;
        val[1] = b;
    }

    float2()
    {
        val[0] = 0.0;
        val[1] = 0.0;
    }

    float2(float2 & param)
    {
        val[0] = param.val[0];
        val[1] = param.val[1];
    }

    void set(float a, float b)
    {
        val[0] = a;
        val[1] = b;
    }
};

struct float3
{
    float val[3];
    float3(float a, float b, float c)
    {
        val[0] = a;
        val[1] = b;
        val[2] = c;
    }

    float3()
    {
        val[0] = 0.0;
        val[1] = 0.0;
        val[2] = 0.0;
    }

    float3(float3 & param)
    {
        val[0] = param.val[0];
        val[1] = param.val[1];
        val[2] = param.val[2];
    }

    void set(float a, float b, float c)
    {
        val[0] = a;
        val[1] = b;
        val[2] = c;
    }
};

struct float4
{
    float val[4];
    float4(float a, float b, float c, float d)
    {
        val[0] = a;
        val[1] = b;
        val[2] = c;
        val[4] = d;
    }

    float4()
    {
        val[0] = 0.0;
        val[1] = 0.0;
        val[2] = 0.0;
        val[3] = 0.0;
    }

    float4(float4 & param)
    {
        val[0] = param.val[0];
        val[1] = param.val[1];
        val[2] = param.val[2];
        val[3] = param.val[3];
    }

    void set(float a, float b, float c, float d)
    {
        val[0] = a;
        val[1] = b;
        val[2] = c;
        val[3] = d;
    }
};



#endif
