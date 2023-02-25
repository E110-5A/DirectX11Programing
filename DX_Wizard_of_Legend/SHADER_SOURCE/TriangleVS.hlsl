#include "globals.hlsli"

VTX_OUT Triangle_VS(VTX_IN In)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    float4 worldPosition = mul(In.vPos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 ProjPosition = mul(viewPosition, projection);
    
    output.vPos = ProjPosition;
    output.vColor = In.vColor;
    output.vUV = In.vUV;
    
    return output;
}