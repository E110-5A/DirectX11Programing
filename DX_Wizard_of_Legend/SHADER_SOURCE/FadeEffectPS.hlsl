#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


//cbuffer FadeEffect : register(b3)
//{
//    float addTime; // 누적시간
//    float duration; // 효과 시간
//    bool  fadeIn; // In, Out 구분
//}

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    //color = defaultTexture.Sample(anisotropicSampler, In.UV);
    
    color.w =  alpha;
    
    return color;
}