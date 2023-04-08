#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);


// 각 스레드가 동기화될 데이터가 필요함 | 최대 스레드 수 : 1024
[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
    
    ParticleBuffer[DTid.x].position += ParticleBuffer[DTid.x].direction 
    * ParticleBuffer[DTid.x].speed * deltaTime;
}