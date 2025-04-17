#include "Common.hlsli"

struct PixelInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord /*uv*/ : TEXCOORD;
    float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
};

// Texture
Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);

SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
    // Sampling.
    float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
    
    float4 tangentNormal = normalMap.Sample(diffuseSampler, input.texCoord);

    // tangent to world transformation matrix.
    float3x3 tangentToWorld = float3x3(
        normalize(input.tangent),
        normalize(input.normal),
        normalize(input.normal)
    );
    
    // Light Dir
    float3 lightDir = -float3(500.0f, 500.0f, -500.0f);
    lightDir = normalize(lightDir);
    
    // World Noraml
    float3 worldNormal = normalize(mul(tangentNormal.xyz, tangentToWorld));
    
    
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
    float specular = CalcBlinnPhone(worldNormal, lightDir, input.cameraDirection);
    
    
    finalColor += specular;

    
    
    return finalColor;

}
