#include "globals.hlsli"

VTX_OUT Triangle_VS(VTX_IN In)
{
    VTX_OUT output = (VTX_OUT) 0.0f;
    
    float4 worldPosition = mul(In.vPos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 projectionPosition = mul(viewPosition, projection);
    
    
    output.vPos = projectionPosition;
    output.vColor = In.vColor;
    output.vUV = In.vUV;
    
    return output;
}