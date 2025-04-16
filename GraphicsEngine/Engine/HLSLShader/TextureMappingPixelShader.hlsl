#include "Common.hlsli"

struct PixelInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord /*uv*/ : TEXCOORD;
    float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1;
};

// Texture
Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
    // Sampling.
    float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
    float4 inputColor = float4(input.color, 1);
    
    // Light Dir
    float3 lightDir = -float3(500.0f, 500.0f, -500.0f);
    lightDir = normalize(lightDir);
    
    // World Noraml
    float3 worldNormal = normalize(input.normal);
    
    // Dot (Labmert cosine Law)
    //float nDotl = saturate(dot(worldNormal, -lightDir));
    float nDotl = CalcLambert(worldNormal, lightDir);
    // Half Lambert
    //float dummy = 0.8f;
    //nDotl = pow(nDotl * dummy + (1.0f - dummy), 1.0f);
    
    //texColor = (1 - texColor);
    


    float4 ambient = texColor * float4(0.1f, 0.1f, 0.1f, 1.0f);
    float4 diffuse = texColor * nDotl;
    float4 finalColor = ambient + diffuse;
    
    // Phong Shader
    // PBR에서 specul에서 색상이 묻으면 금속 아니면 비금속

    //float specular = CalcPhong(worldNormal, lightDir, input.cameraDirection);
    
    // Blinn-Phong (specular)
    float specular = 0;
    if (nDotl)
    {
        // Half Vector
        float3 viewDirection = normalize(input.cameraDirection);
        float3 halfVector = normalize((-lightDir) + (-viewDirection));

        // nDoth
        float nDoth = saturate(dot(worldNormal, halfVector));
        float shininess = 32.0f;
        specular = pow(nDoth, shininess);
    }
    
    finalColor += float4(0.4f, 0.6f, 0.8f, 1) * specular;

    
    
    return finalColor;

}
