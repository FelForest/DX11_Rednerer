struct VertexInput
{
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texCoord /*uv*/ : TEXCOORD;
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
    ouput.position = float4(input.position, 1);
    ouput.color = input.color;
    ouput.texCoord = input.texCoord;
    
    return ouput;
}

// �Է��� �߰��Ǹ� ��µ� �߰��Ǿ���