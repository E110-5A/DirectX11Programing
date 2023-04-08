#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    uint iInstance : SV_InstanceID;
};

struct VSOut
{
    float4 Pos : SV_Position;
    uint iInstance : SV_InstanceID;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    // 좌표계산을 VS가 아닌 GS에서 진행한다
    Out.Pos = In.Pos;
    Out.iInstance = In.iInstance;
    
    return Out;    
}