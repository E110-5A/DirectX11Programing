RWTexture2D<float4> tex : register(u0);


//  SV_GroupID  : 스레드에 속한 그룹의 좌표
//  SV_GroupThreadID : 그룹 내에서, 스레드의 좌표
//  SV_GroupIndex : 그룹 내에서, 스레드의 인덱스 좌표(1차원)
//  SV_DispatchThreadID : 전체 스레드기준으로 호출된 좌표

[numthreads(32, 32, 1)] // 그룹당 스레드 개수 (최대 1024)
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (1024 <= DTid.x || 1024 <= DTid.y)
        return;
    tex[DTid.xy] = float4(0, 1.0f, 1.0f, 1.0f);
}