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
    uint iInstance : SV_InstanceID;
};

StructuredBuffer<Particle> particleBuffer : register(t15);

[maxvertexcount(6)]
void main(point VSOut Input[1], inout TriangleStream<GSOutput> Out)
{
    // 반환할 자료형 생성
    GSOutput rect[4] = { (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f };
    
    // active가 아니면 종료
    if (0 == particleBuffer[Input[0].iInstance].active)
        return;
    
    
    
    // 좌표 계산
    float3 vWorldPos = Input[0].Pos.xyz + particleBuffer[Input[0].iInstance].position.xyz;
    
    if (0 == simulationSpace)
    {
        vWorldPos += world._41_42_43;
    }    
    float3 vViewPos = mul( float4( vWorldPos, 1.0f ), view ).xyz;
    float3 vScale = particleSize.xyz;
    
    
    
    
    // 사각형 형태정보 만들기
    float3 rectPos[4] =
    {
        vViewPos + float3(-0.5f, 0.5f, 0.0f) * vScale,
        vViewPos + float3(0.5f, 0.5f, 0.0f) * vScale,
        vViewPos + float3(0.5f, -0.5f, 0.0f) * vScale,
        vViewPos + float3(-0.5f, -0.5f, 0.0f) * vScale
    };

    // 사각형 위치값 채워넣기
    for (int index = 0; index < 4; ++index)
    {
        rect[index].Pos = mul( float4( rectPos[index], 1.0f ), projection );
    }
    
    // UV값 넣기
    rect[0].UV = float2(0.0f, 0.0f);
    rect[1].UV = float2(1.0f, 0.0f);
    rect[2].UV = float2(1.0f, 1.0f);
    rect[3].UV = float2(0.0f, 1.0f);

    rect[0].iInstance = Input[0].iInstance;
    rect[1].iInstance = Input[0].iInstance;
    rect[2].iInstance = Input[0].iInstance;
    rect[3].iInstance = Input[0].iInstance;
    
    
    // 정점 추가하기 (GS 기능)
    Out.Append(rect[0]);
    Out.Append(rect[1]);
    Out.Append(rect[2]);
    Out.RestartStrip();
    Out.Append(rect[0]);
    Out.Append(rect[2]);
    Out.Append(rect[3]);
    Out.RestartStrip();    
}