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

// Camera Buffer
cbuffer Camera : register(b1)
{
    matrix view;
};


struct VertexOutput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord /*uv*/ : TEXCOORD;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    //ouput.position = float4(input.position, 1);
    output.position = mul(float4(input.position, 1), worldMatrix);
    output.position = mul(output.position, view);
    
    output.color = input.color;
    output.texCoord = input.texCoord;
    
    return output;
}

// 입력이 추가되면 출력도 추가되야함