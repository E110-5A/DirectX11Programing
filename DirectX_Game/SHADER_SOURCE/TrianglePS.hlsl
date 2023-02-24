struct VTX_OUT
{
    float4 vPos : SV_POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

Texture2D defaultTexture : register(t0);

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

float4 Triangle_PS(VTX_OUT In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    
    color = defaultTexture.Sample(anisotropicSampler, In.vUV);
    
    return color;
}