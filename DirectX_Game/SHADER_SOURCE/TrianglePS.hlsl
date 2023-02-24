struct VTX_OUT
{
    float4 vPos : SV_POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

Texture2D defaultTexture : register(t0);
SamplerState samplerState : register(s0);

float4 Triangle_PS(VTX_OUT In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    
    color = defaultTexture.Sample(samplerState, In.vUV);
    
    return color;
}