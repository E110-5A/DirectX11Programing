#include "globals.hlsli"

float4 Triangle_PS(VTX_OUT In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    
    color = defaultTexture.Sample(anisotropicSampler, In.vUV);
    
    return color;
}