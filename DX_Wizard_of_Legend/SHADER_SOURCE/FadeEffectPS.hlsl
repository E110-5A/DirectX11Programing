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
        
    float ratio = (addTime / duration);
    
    // 알파 값 감소 (Fade-In)
    if (true == fadeIn)
        color.w = 255 * ratio;
    
    // 알파 값 증가 (Fade-Out)
    else
        color.w = 255 * (1 - ratio);
    
    return color;
}