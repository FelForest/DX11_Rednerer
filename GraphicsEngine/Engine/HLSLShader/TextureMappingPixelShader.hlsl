struct PixelInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord /*uv*/ : TEXCOORD;
    float3 normal : NORMAL;
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
    
    // Dot
    float nDotL = saturate(dot(worldNormal, -lightDir));

    // Half Lambert
    float dummy = 0.8f;
    nDotL = pow(nDotL * dummy + (1.0f - dummy), 1.0f);
    
    //texColor = (1 - texColor);
    float4 finalColor = texColor * nDotL;
    
    
    
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
    //return float4(input.color, 1.0f);
    //return float4(input.texCoord, 0.0f, 1.0f);
    //return float4(lightIntensity, lightIntensity, lightIntensity, 1);
    
    return finalColor;

}
