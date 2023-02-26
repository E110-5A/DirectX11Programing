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
//    float addTime; // �����ð�
//    float duration; // ȿ�� �ð�
//    bool  fadeIn; // In, Out ����
//}

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    //color = defaultTexture.Sample(anisotropicSampler, In.UV);
        
    float ratio = (addTime / duration);
    
    // ���� �� ���� (Fade-In)
    if (true == fadeIn)
        color.w = 255 * ratio;
    
    // ���� �� ���� (Fade-Out)
    else
        color.w = 255 * (1 - ratio);
    
    return color;
}