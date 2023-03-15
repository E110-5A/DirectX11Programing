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
        // ������?
        float2 diff = (atlasSize - spriteSize) / 2.0f;        
        // ȭ�鿡 �׷��� UV ��ǥ �ȼ���
        float2 UV = (leftTop - diff - offset) + (atlasSize * In.UV);
        
        // UV �ȼ��� ��������Ʈ ������ ����� discard
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