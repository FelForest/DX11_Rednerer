struct VertexInput
{
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texCoord /*uv*/ : TEXCOORD;
    float3 normal : NORMAL;
};

cbuffer Transform : register(b0)
{
    matrix worldMatrix;
};

// Camera Buffer
cbuffer Camera : register(b1)
{
    matrix view;
    matrix projection;
};


struct VertexOutput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord /*uv*/ : TEXCOORD;
    float3 normal : NORMAL;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    //ouput.position = float4(input.position, 1);
    output.position = mul(float4(input.position, 1), worldMatrix);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    
    
    // 모든건 같은 공간에서 이루어 져야함
    output.color = input.color;
    output.texCoord = input.texCoord;
    
    // 방법 2가지 행렬을 늘려서 계산후 다시 줄이기
    // 행렬을 줄여서 계산하기
    output.normal = normalize(mul(input.normal, (float3x3)worldMatrix));
    return output;
}

// 입력이 추가되면 출력도 추가되야함