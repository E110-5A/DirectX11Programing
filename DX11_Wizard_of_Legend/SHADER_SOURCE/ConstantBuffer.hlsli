cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}
cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}
cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}
cbuffer Fade : register(b3)
{
    float alpha;
}
cbuffer Animation : register(b4)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;
    
    uint animationType;
}
cbuffer NumberOfLight : register(b5)
{
    uint numberOfLight;
}

cbuffer ParticleSystem : register(b6)
{
    float4 particleWorldPosition;
    float4 particleColor;
    float4 particleSize;

    uint maxParticles;
    uint simulationSpace;
    float particleRadius;
    float particleSpeed;

    float particleLifeTime;
    float particleDeltaTime;
    float particleElapsedTime;
    int padding;
}

//cbuffer noise : register(b7)
//{
//    float4 noiseSize;
//}