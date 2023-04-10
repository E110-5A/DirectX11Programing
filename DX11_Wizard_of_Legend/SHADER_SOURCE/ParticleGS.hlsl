#include "globals.hlsli"

struct VSOut
{
    float4 Pos : SV_Position;
    uint iInstance : SV_InstanceID;
};

struct GSOutput
{
	float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};

StructuredBuffer<Particle> particleBuffer : register(t15);

[maxvertexcount(6)]
void main(point VSOut Input[1], inout TriangleStream<GSOutput> Out)
{
    // ��ȯ�� �ڷ��� ����
    GSOutput rect[4] = { (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f };
    
    // active�� �ƴϸ� ����
    if (0 == particleBuffer[Input[0].iInstance].active)
        return;
    
    // ��ǥ ���
    float3 vWorldPos = Input[0].Pos.xyz + particleBuffer[Input[0].iInstance].position.xyz;
    float3 vViewPos = mul(float4(vWorldPos, 1.0f), view);
    
    // �簢�� �������� �����
    float3 rectPos[4] =
    {
        vViewPos + float3(-0.5f, 0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f),
        vViewPos + float3(0.5f, 0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f),
        vViewPos + float3(0.5f, -0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f),
        vViewPos + float3(-0.5f, -0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f)
    };

    // �簢�� ��ġ�� ä���ֱ�
    for (int index = 0; index < 4; ++index)
    {
        rect[index].Pos = mul(float4(rectPos[index], 1.0f), projection);
    }
    
    // UV�� �ֱ�
    rect[0].UV = float2(0.0f, 0.0f);
    rect[1].UV = float2(1.0f, 0.0f);
    rect[2].UV = float2(1.0f, 1.0f);
    rect[3].UV = float2(0.0f, 1.0f);

    // ���� �߰��ϱ� (GS ���)
    Out.Append(rect[0]);
    Out.Append(rect[1]);
    Out.Append(rect[2]);
    Out.RestartStrip();
    Out.Append(rect[0]);
    Out.Append(rect[2]);
    Out.Append(rect[3]);
    Out.RestartStrip();    
}