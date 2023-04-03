#include "globals.hlsli"

struct VSOut
{
    float4 Pos : SV_Position;
    uint iInstance : SV_InstanceID;
};

struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
};

[maxvertexcount(6)]
void main(point VSOut Input[1], inout TriangleStream<GSOut> Out)
{
    GSOut rect[4] = { (GSOut) 0.0f, (GSOut) 0.0f, (GSOut) 0.0f, (GSOut) 0.0f };
    
    if (0 == particleBuffer[Input[0].iInstance].active)
        return;
    
    float3 vWorldPos = Input[0].Pos.xyz + particleBuffer[Input[0].iInstance].position.xyz;
    float3 vViewPos = mul(float4(vWorldPos, 1.0f), view);
    
    float3 newPos[4] =
    {
        vViewPos + float3(-0.5f, 0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f),
        vViewPos + float3(0.5f, 0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f),
        vViewPos + float3(0.5f, -0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f),
        vViewPos + float3(-0.5f, -0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f)
    };

    for (int count = 0; count < 4; ++count)
    {
        rect[count].Pos = mul(float4(newPos[count], 1.0f), projection);
    }
    
    rect[0].UV = float2(0.0f, 0.0f);
    rect[1].UV = float2(1.0f, 0.0f);
    rect[2].UV = float2(1.0f, 1.0f);
    rect[3].UV = float2(0.0f, 1.0f);

    Out.Append(rect[0]);
    Out.Append(rect[1]);
    Out.Append(rect[2]);
    Out.RestartStrip();
    Out.Append(rect[0]);
    Out.Append(rect[2]);
    Out.Append(rect[3]);
    Out.RestartStrip();    
}