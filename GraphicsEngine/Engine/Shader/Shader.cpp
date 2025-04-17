#include "Shader.h"
#include <d3dcompiler.h>
#include "../Core/Engine.h"

namespace GE
{
	Shader::Shader(const std::wstring& name)
		: name(name)
	{

		// 경로 추가
		wchar_t path[256];
		swprintf_s(path, 256, L"../CompiledShader/%sVertexShader.cso", name.c_str());

		//  버텍스 쉐이더 컴파일
		//auto result = D3DCompileFromFile(
		//	path,
		//	nullptr, 
		//	/*쉐이더 안에 다른 파일 포함시키는거 설정값 */nullptr, 
		//	"main", 
		//	"vs_5_0", 
		//	0, 
		//	0, 
		//	&vertexShaderBuffer, 
		//	nullptr
		//);
		//if (FAILED(result))
		//{
		//	MessageBox(nullptr, TEXT("Failed to compile vertex shader. "), TEXT("Error"), MB_OK);
		//	__debugbreak();
		//}

		// 장치 객체 얻어오기
		auto& device = Engine::Get().Device();

		// 버텍스 CSO 로드
		auto result = D3DReadFileToBlob(path, &vertexShaderBuffer);
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to read vertex shader object. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// 버텍스 쉐이더 생성
		result = device.CreateVertexShader(
			vertexShaderBuffer->GetBufferPointer(), 
			vertexShaderBuffer->GetBufferSize(), 
			nullptr, 
			&vertexShader
		);
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create vertex shader. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// 입력 레이아웃
		// 정점 쉐이더에 전달할 정점 데이터가 어떻게 생겼는지 알려줌
		/*
		LPCSTR SemanticName;
		UINT SemanticIndex;
		DXGI_FORMAT Format;
		UINT InputSlot;
		UINT AlignedByteOffset;
		D3D11_INPUT_CLASSIFICATION InputSlotClass;
		UINT InstanceDataStepRate;
		*/
		D3D11_INPUT_ELEMENT_DESC inputDesc[] =
		{
			{
				"POSITION",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT, /*0*/
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			},
			{
				"COLOR",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT /*12*/,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			},
			{
				"TEXCOORD",
				0,
				DXGI_FORMAT_R32G32_FLOAT,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT /*24*/,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			},
			{
				"NORMAL",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT /*32*/,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			},
		{
			"TANGENT",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT /*44*/,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
			{
			"BITANGENT",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT /*56*/,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}


		};
		// DX에 리플렉션 하는게 있음
		result = device.CreateInputLayout(
			inputDesc,
			_countof(inputDesc),
			vertexShaderBuffer->GetBufferPointer(), 
			vertexShaderBuffer->GetBufferSize(), 
			&inputlayout
		);
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create input layout. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// 픽셀 쉐이더 컴파일/생성
		// 각 리소스 바인딩.

		// 픽셀 CSO 로드
		swprintf_s(path, 256, L"../CompiledShader/%sPixelShader.cso", name.c_str());

		result = D3DReadFileToBlob(path, &pixelShaderBuffer);

		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to read pixel shader object. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}
		// 픽셀 쉐이더 컴파일
		//ID3DBlob* pixelShaderBuffer = nullptr;
		//result = D3DCompileFromFile(path, 
		//	nullptr, 
		//	/*쉐이더 안에 다른 파일 포함시키는거 설정값 */nullptr, 
		//	"main", 
		//	"ps_5_0", 
		//	0, 
		//	0, 
		//	&pixelShaderBuffer, 
		//	nullptr
		//);
		//if (FAILED(result))
		//{
		//	MessageBox(nullptr, TEXT("Failed to compile pixel shader. "), TEXT("Error"), MB_OK);
		//	__debugbreak();
		//}

		// 버텍스 쉐이더 생성
		result = device.CreatePixelShader(
			pixelShaderBuffer->GetBufferPointer(), 
			pixelShaderBuffer->GetBufferSize(), 
			nullptr, 
			&pixelShader
		);
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create pixel shader. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}
	}
	Shader::~Shader()
	{
		// DX 리소스 해제
		if (inputlayout)
		{
			inputlayout->Release();
		}

		if (vertexShader)
		{
			vertexShader->Release();
		}

		if (vertexShaderBuffer)
		{
			vertexShaderBuffer->Release();
		}

		if (pixelShader)
		{
			pixelShader->Release();
		}

		if (pixelShaderBuffer)
		{
			pixelShaderBuffer->Release();
		}
	}

	void Shader::Bind()
	{
		// 장치 문맥(DeviceContext) 얻어오기
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 입력 레이아웃 전달
		context.IASetInputLayout(inputlayout);
		// 조립할 모양 설정
		context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 쉐이더 설정
		context.VSSetShader(vertexShader, nullptr, 0);
		context.PSSetShader(pixelShader, nullptr, 0);
	}
}