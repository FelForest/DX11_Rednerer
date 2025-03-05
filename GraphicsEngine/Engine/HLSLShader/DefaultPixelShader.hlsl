struct PixelInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord /*uv*/ : TEXCOORD;
};



float4 main(PixelInput input) : SV_TARGET
{
 //   // Sampling.
 //   float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
 //   float4 inputColor = float4(input.color, 1);
    
 //   texColor = (1 - texColor);
 //   float4 finalColor = texColor * inputColor;
    
 //   finalColor = (1 - finalColor);
    
    
	////return float4(1.0f, 0.0f, 0.0f, 1.0f);
        return float4(input.color, 1.0f);
 //   //return float4(input.texCoord, 0.0f, 1.0f);
    
 //   return finalColor;
}
