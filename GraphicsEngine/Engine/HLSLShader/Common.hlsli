// Lambert
float CalcLambert(float3 worldNormal, float3 lightDirection)
{
    return saturate(dot(worldNormal, -lightDirection));
}

// Half Lambert
float CalcHalfLambert(float3 worldNormal, float3 lightDirection, float param1 = 0.5f, float param2 = 2)
{
    float nDotL = CalcLambert(worldNormal, lightDirection);
    param1 = clamp(param1, 0.0f, 1.0f);
    return pow(nDotL * param1 + (1.0f - param1) , param2);
}