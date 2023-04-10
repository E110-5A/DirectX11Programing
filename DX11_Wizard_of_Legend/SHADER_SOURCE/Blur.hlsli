Texture2D NoiseTexture : register(t16);

cbuffer Noise : register(b7)
{
    float4 noiseSize;
}

static float GaussianFilter[5][5] =
{
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
};

float4 GaussianBlur(float2 UV)
{
    float4 Out = (float4) 0.0f;
    
    // noise Texture에서 무작위 UV좌표로부터 색상 값을 받음
    
    // 해당 좌표의 색상값이 1보다 큰경우 정수를 처내고 소숫점만 가져옴
    if (1.f < UV.x)
        UV.x = frac(UV.x);
    else if (UV.x < 0.0f)
        UV.x = 1.0f + frac(UV.x);
    
    if (1.f < UV.y)
        UV.y = frac(UV.y);
    else if (UV.y < 0.0f)
        UV.y = 1.0f + frac(UV.y);
    
    // 실사용할 UV좌표를 noiseTexture의 크기만큼 곱하여 구한다
    int2 iUV = UV * noiseSize.xy;
    iUV -= int2(2, 2);
    
    // 랜덤 값 구하기
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            int2 idx = int2(iUV.y + i, iUV.x + j);
            Out += NoiseTexture[idx] * GaussianFilter[i][j];
        }
    }
    
    return Out;
}