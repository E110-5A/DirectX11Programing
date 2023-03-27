#include "Light.hlsli"

cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}
cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}
cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}
cbuffer Fade : register(b3)
{    
    float alpha;
}
cbuffer Animation : register(b4)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;
    
    uint animationType;
}
cbuffer NumberOfLight : register(b5)
{
    uint numberOfLight;
}
cbuffer Random : register(b6)
{
    float random;
}

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

StructuredBuffer<LightAttribute> lightAttributes : register(t13);

Texture2D defaultTexture : register(t0);
Texture2D atlasTexture : register(t12);

void Calculate(in out LightColor pLightColor, float3 position, int idx)
{
    // Directional
    if (0 == lightAttributes[idx].type)
    {
        pLightColor.diffuse += lightAttributes[idx].color.diffuse;
    }
    // point
    else if (1 == lightAttributes[idx].type)
    {
        float length = distance(lightAttributes[idx].position.xy, position.xy);
        
        if (length < lightAttributes[idx].radius)
        {
            float ratio = 1.0f - (length / lightAttributes[idx].radius);
            pLightColor.diffuse += lightAttributes[idx].color.diffuse * ratio;
        }
    }
    // spot
    else
    {
        
    }
}