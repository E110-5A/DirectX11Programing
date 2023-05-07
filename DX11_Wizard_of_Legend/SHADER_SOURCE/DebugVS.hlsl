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


float4 main(float4 pos : POSITION) : SV_POSITION
{
    //VSOut Out = (VSOut) 0.f;
    
    //float4 worldPosition = mul(In.Pos, world);
    //float4 viewPosition = mul(worldPosition, view);
    //float4 ProjPosition = mul(viewPosition, projection);
    
    //Out.Pos = ProjPosition;
    //Out.WorldPos = worldPosition;
    //Out.Color = In.Color;
    //Out.UV = In.UV;
    
    //return Out;    
    
    float4 worldPosition = mul(pos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 ProjPosition = mul(viewPosition, projection);
    
    return ProjPosition;
}
