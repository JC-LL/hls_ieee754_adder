#include <cstdint>
#include <cstring>

uint32_t float_as_uint32 (float a)
{
    uint32_t r;
    memcpy (&r, &a, sizeof r);
    return r;
}

float uint32_as_float (uint32_t a)
{
    float r;
    memcpy (&r, &a, sizeof r);
    return r;
}
