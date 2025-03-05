struct VertexInput
{
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texCoord /*uv*/ : TEXCOORD;
};

cbuffer Transform : register(b0)
{
    matrix worldMatrix;
};

struct VertexOutput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord /*uv*/ : TEXCOORD;
};

VertexOutput main(VertexInput input)
{
    VertexOutput ouput;
    //ouput.position = float4(input.position, 1);
    ouput.position = mul(float4(input.position, 1), worldMatrix);
    ouput.color = input.color;
    ouput.texCoord = input.texCoord;
    
    return ouput;
}

// 입력이 추가되면 출력도 추가되야함