#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

// 각 스레드가 동기화될 데이터가 필요함 | 최대 스레드 수 : 1024
[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (maxParticles <= DTid.x)
        return;
    
    if (0 == ParticleBuffer[DTid.x].active)
    {
        while (0 < ParticleSharedBuffer[0].gActiveCount)
        {
            // Active 값 준비하기
            int originValue = ParticleSharedBuffer[0].gActiveCount;
            int exchange = originValue - 1;
        
            // 스레드 동기화하기
            //InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange);
            InterlockedCompareExchange(ParticleSharedBuffer[0].gActiveCount, originValue, exchange, exchange);
            
            if (originValue == exchange)
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
        
        if (ParticleBuffer[DTid.x].active)
        {
            float4 Random = (float4) 0.0f;
            float2 UV = float2( (float)DTid.x / maxParticles, 0.5f );
            UV.x += particleElapsedTime;
            UV.y += sin( (UV.x + particleElapsedTime) * 3.141592f + 2.0f * 10.0f ) * 0.5f;
            
            Random = float4
                (
                    GaussianBlur(UV + float2(0.0f, 0.0f)).x
                    , GaussianBlur(UV + float2(0.1f, 0.0f)).x
                    , GaussianBlur(UV + float2(0.2f, 0.0f)).x
                    , GaussianBlur(UV + float2(0.3f, 0.0f)).x
                );
            
            // 원형 범위로 스폰
            float fTheta = Random.xy * 3.141592f * 2.0f;
            ParticleBuffer[DTid.x].position.xy = float2( cos(fTheta), sin(fTheta) ) * Random.y * particleRadius;
            ParticleBuffer[DTid.x].position.z = 100.0f;
            
            ParticleBuffer[DTid.x].direction.xy 
                    = normalize( float2( ParticleBuffer[DTid.x].position.xy ) );
            
            // 0 local, 1 world
            if (simulationSpace)
            {
                ParticleBuffer[DTid.x].position.xyz += particleWorldPosition.xyz;
            }
            ParticleBuffer[DTid.x].time = 0.0f;
            ParticleBuffer[DTid.x].speed = particleSpeed;
            ParticleBuffer[DTid.x].lifeTime = particleLifeTime;
        }
    }
    else
    {
        ParticleBuffer[DTid.x].time += particleDeltaTime;
        if (ParticleBuffer[DTid.x].lifeTime < ParticleBuffer[DTid.x].time)
        {
            ParticleBuffer[DTid.x].active = 0;
        }
        else
        {
            ParticleBuffer[DTid.x].position
                    += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * particleDeltaTime;

        }
    }
    
    
}