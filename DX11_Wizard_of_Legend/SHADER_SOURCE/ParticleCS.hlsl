#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

// �� �����尡 ����ȭ�� �����Ͱ� �ʿ��� | �ִ� ������ �� : 1024
[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
    
    
    
    
    if (0 == ParticleBuffer[DTid.x].active)
    {
        while (0 < ParticleSharedBuffer[0].gActiveCount)
        {
            // Active �� �غ��ϱ�
            int originValue = ParticleSharedBuffer[0].gActiveCount;
            int exchange = originValue - 1;
        
        // ������ ����ȭ�ϱ�
            InterlockedExchange(ParticleSharedBuffer[0].gActiveCount, exchange, exchange);
        
            if (originValue == exchange)
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
    }
    else
    {
        ParticleBuffer[DTid.x].position += ParticleBuffer[DTid.x].direction 
            * ParticleBuffer[DTid.x].speed * deltaTime;
    }
    
    
}