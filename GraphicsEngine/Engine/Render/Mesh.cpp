#include "Mesh.h"
#include "../Core/Engine.h"
#include "../Shader/Shader.h"

namespace GE
{
	MeshData::MeshData()
	{
	}
	MeshData::MeshData(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices)
	{
		// 파라미터 복사
		this->vertices.assign(vertices.begin(), vertices.end());
		stride = Vertex::Stride();
		this->indices.assign(indices.begin(), indices.end());

		// @Temp : 임시 리소스 생성
		// 버퍼(Buffer) - 메모리 덩어리
		D3D11_BUFFER_DESC vertexBufferDesc = { };
		vertexBufferDesc.ByteWidth = stride * (uint32)vertices.size();
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = { };
		vertexData.pSysMem = vertices.data();

		ID3D11Device& device = Engine::Get().Device();
		// (정점) 버퍼 생성
		auto result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create vertex buffer. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// @Temp : 임시 리소스 생성
		// 버퍼(Buffer) - 메모리 덩어리
		D3D11_BUFFER_DESC indexBufferDesc = { };
		indexBufferDesc.ByteWidth = sizeof(uint32) * (uint32)indices.size();
		indexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = { };
		indexData.pSysMem = indices.data();

		// (인덱스) 버퍼 생성
		result = device.CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create index buffer. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}
	}
	MeshData::~MeshData()
	{
		if (vertexBuffer)
		{
			vertexBuffer->Release();
		}
		if (indexBuffer)
		{
			indexBuffer->Release();
		}
	}
	void MeshData::Bind()
	{
		// 컨텍스트 얻어오기
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 정점/인덱스 버퍼 바인딩
		static uint32 offset = 0;
		context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}
	Mesh::Mesh()
	{
	}
	void Mesh::Draw()
	{
		// 컨텍스트 얻어오기
		ID3D11DeviceContext& context = Engine::Get().Context();

		// 루프 순회하면서 바인딩 & 드로우
		for (int ix = 0; ix < (int32)meshes.size(); ++ix)
		{
			meshes[ix]->Bind();
			shaders[ix]->Bind();
			context.DrawIndexed(meshes[ix]->IndexCount(), 0, 0);
		}
	}
}
