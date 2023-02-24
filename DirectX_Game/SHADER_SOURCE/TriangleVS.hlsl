struct VTX_IN
{
    float4 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPos : SV_POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;    
};

cbuffer Transform : register(b0)
{
    float4 cbPos;
}

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

VTX_OUT Triangle_VS(VTX_IN In)
{
    VTX_OUT output = (VTX_OUT) 0.0f;
    output.vPos = float4(In.vPos + cbPos);
    output.vColor = In.vColor;
    output.vUV = In.vUV;
    
    return output;
}