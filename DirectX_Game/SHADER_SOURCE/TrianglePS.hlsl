struct VTX_OUT
{
    float4 vPos : SV_POSITION;
    float4 vColor : COLOR;
};

float4 Triangle_PS(VTX_OUT In) : SV_TARGET
{
    return In.vColor;
}