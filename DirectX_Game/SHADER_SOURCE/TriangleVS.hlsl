struct VTX_IN
{
    float3 vPos : POSITION;
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
    float3 cbPos;
}

VTX_OUT Triangle_VS(VTX_IN In)
{
    VTX_OUT output = (VTX_OUT) 0.0f;
    output.vPos = float4(In.vPos + cbPos.xyz, 1.f);
    output.vColor = In.vColor;
    output.vUV = In.vUV;
    
    return output;
}