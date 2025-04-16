// Lambert
float CalcLambert(float3 worldNormal, float3 lightDirection)
{
    return saturate(dot(worldNormal, -lightDirection));
}

// Half Lambert
float CalcHalfLambert(float3 worldNormal, float3 lightDirection, float param1 = 0.5f, float param2 = 2)
{
    float nDotl = CalcLambert(worldNormal, lightDirection);
    param1 = clamp(param1, 0.0f, 1.0f);
    return pow(nDotl * param1 + (1.0f - param1) , param2);
}

// Phong
float CalcPhong(float3 worldNormal, float3 lightDirection, float3 cameraDirection, float shininess = 16.0f)
{
    float nDotl = CalcLambert(worldNormal, lightDirection);
    
    float specular = 0;
    if (nDotl)
    {
        float3 reflection = reflect(lightDirection, worldNormal);
        float3 viewDirection = normalize(cameraDirection);
        float rDotv = saturate(dot(reflection, -viewDirection));
        specular = pow(rDotv, shininess);
    }

    return specular;
}