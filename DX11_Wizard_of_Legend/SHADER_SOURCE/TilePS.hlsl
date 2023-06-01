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
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    
    // Animation
    if (1 == animationType) // 2D
    {
        // ������?
        float2 diff = (tilesetSize - tileSize) / 2.0f;
        // ȭ�鿡 �׷��� UV ��ǥ �ȼ���
        float2 UV = (tileLT - diff) + (tilesetSize * In.UV);
        
        // UV �ȼ��� ��������Ʈ ������ ����� discard
        if (UV.x < tileLT.x || UV.y < tileLT.y
            || UV.x > tileLT.x + tileSize.x
            || UV.y > tileLT.y + tileSize.y)
            discard;
        
        color = atlasTexture.Sample(pointSampler, UV);
    }
    else
    {
        color = defaultTexture.Sample(pointSampler, In.UV);
    }
    
    // Light
    LightColor lightColor = (LightColor) 0.0f;
    
    for (int idx = 0; idx < numberOfLight; ++idx)
    {
        Calculate(lightColor, In.WorldPos.xyz, idx);
    }
    
    color *= lightColor.diffuse;
    
    return color;
}