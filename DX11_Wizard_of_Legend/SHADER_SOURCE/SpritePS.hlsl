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

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    
    if (1 == animationType) // 2D
    {
        // 차이점?
        float2 diff = (atlasSize - spriteSize) / 2.0f;        
        // 화면에 그려질 UV 좌표 픽셀값
        float2 UV = (leftTop - diff - offset) + (atlasSize * In.UV);
        
        // UV 픽셀이 스프라이트 범위를 벗어나면 discard
        if (UV.x < leftTop.x || UV.y < leftTop.y
            || UV.x > leftTop.x + spriteSize.x
            || UV.y > leftTop.y + spriteSize.y)
            discard;
        
        color = atlasTexture.Sample(pointSampler, UV);
    }
    else
    {
        color = defaultTexture.Sample(pointSampler, In.UV);
    }
    
    return color;
}