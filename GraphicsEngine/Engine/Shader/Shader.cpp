#include "Shader.h"
#include <d3dcompiler.h>
#include "../Core/Engine.h"

namespace GE
{
	Shader::Shader(const std::wstring& name)
		: name(name)
	{

		// ��� �߰�
		wchar_t path[256];
		swprintf_s(path, 256, L"HLSLShader/%sVertexShader.hlsl", name.c_str());
		// ���̴� ������
		auto result = D3DCompileFromFile(
			path,
			nullptr, 
			/*���̴� �ȿ� �ٸ� ���� ���Խ�Ű�°� ������ */nullptr, 
			"main", 
			"vs_5_0", 
			0, 
			0, 
			&vertexShaderBuffer, 
			nullptr
		);
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to compile vertex shader. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		auto& device = Engine::Get().Device();

		// ���̴� ����
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

		// �Է� ���̾ƿ�
		// ���� ���̴��� ������ ���� �����Ͱ� ��� ������� �˷���
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
				0,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			},
			{
				"COLOR",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			}
		};
		// DX�� ���÷��� �ϴ°� ����
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

		// �ȼ� ���̴� ������/����
		// �� ���ҽ� ���ε�.

		swprintf_s(path, 256, L"HLSLShader/%sPixelShader.hlsl", name.c_str());
		// ���̴� ������
		ID3DBlob* pixelShaderBuffer = nullptr;
		result = D3DCompileFromFile(path, 
			nullptr, 
			/*���̴� �ȿ� �ٸ� ���� ���Խ�Ű�°� ������ */nullptr, 
			"main", 
			"ps_5_0", 
			0, 
			0, 
			&pixelShaderBuffer, 
			nullptr
		);
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to compile pixel shader. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// ���̴� ����
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
		// DX ���ҽ� ����
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
		// ��ġ ����(DeviceContext) ������
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// �Է� ���̾ƿ� ����
		context.IASetInputLayout(inputlayout);
		// ������ ��� ����
		context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ���̴� ����
		context.VSSetShader(vertexShader, nullptr, 0);
		context.PSSetShader(pixelShader, nullptr, 0);
	}
}