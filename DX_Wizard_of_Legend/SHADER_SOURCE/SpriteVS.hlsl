#include "globals.hlsli"


VSOut Sprite_VS(VSIn In)
{
    VSOut output = (VSOut) 0.f;
    
    float4 worldPosition = mul(In.Pos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 ProjPosition = mul(viewPosition, projection);
    
    output.Pos = ProjPosition;
    output.Color = In.Color;
    output.UV = In.UV;
    
    return output;
}