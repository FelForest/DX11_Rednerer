#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>

namespace GE
{
	Renderer::Renderer(uint32 width, uint32 height, HWND window)
	{
		// ��ġ ������ ����ϴ� �ɼ�
		uint32 flag = 0u;

#if _DEBUG
		// ����� ������ �� ����
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// ������ ���̺귯�� ����
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			// �õ��� ���� �ȵǸ� ������ �Ѵٴ� ����
			// �ֽ� ������ ���� ���� �ִ°� ����
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		// ���� ü�� ���� ����ü
		/*
		DXGI_MODE_DESC BufferDesc;
		DXGI_SAMPLE_DESC SampleDesc;
		DXGI_USAGE BufferUsage;
		UINT BufferCount;
		HWND OutputWindow;
		BOOL Windowed;
		DXGI_SWAP_EFFECT SwapEffect;
		UINT Flags;
		*/

		// ��Ƽ ���ø� ����� ���� Ȯ��



		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		// â ���
		swapChainDesc.Windowed = true;									
		swapChainDesc.OutputWindow = window;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		// ����� ����
		swapChainDesc.BufferCount = 1;									

		// ���ϸ���� / �ٸ����
		// ��Ƽ ���ø� ����
		// 1���� �Ⱦ��ٴ� ��
		swapChainDesc.SampleDesc.Count = 1;		
		// ��Ƽ ���ø� ����
		swapChainDesc.SampleDesc.Quality = 0;							

		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// ���� ���� ���
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


		// ��ġ ����
		// �̰� �Ұ� ������ -> �������� �� �� ����
		//D3D11CreateDevice;

		
		// 3���� ����
		HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flag, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, /*�����쿡 ���� �ǰ� ���� ��ũ�η� �Ȱ�*/ &swapChainDesc, &swapChain, &device, nullptr, &context);

		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create devices. "), TEXT("Error"), MB_OK);
			__debugbreak();
			
		}

		// ���� Ÿ�� �� ����.
		ID3D11Texture2D* backbuffer = nullptr;

		// ���� �޾ƿ���
		//swapChain->GetBuffer(0, __uuidof(backbuffer), reinterpret_cast<void**>(&backbuffer));
		result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to get back buffer. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		result = device->CreateRenderTargetView(backbuffer, nullptr, &renderTargetView);

		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create render target view. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// ���� Ÿ�� �� ���ε�(����)
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);
		// ������ ���� ���� ���� �� ����� ���߿� ���� ����

		// �� ��Ʈ(ȭ��)
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;

		// ����Ʈ ����
		context->RSSetViewports(1, &viewport);

		// ���� ������ ����
		float vertices[] =
		{
			 0.0f,  0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
		};

		// @Temp : �ӽ� ���ҽ� ����
		// ����(Buffer) - �޸� ���
		D3D11_BUFFER_DESC vertexBufferDesc = { };
		vertexBufferDesc.ByteWidth = sizeof(float) * 3 * 3;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = { };
		vertexData.pSysMem = vertices;

		// (����) ���� ����
		result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create vertex buffer. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// �ε���(����) ���� ����(���� �����ϴ� ����)
		int indices[] =
		{
			0, 1, 2
		};

		// @Temp : �ӽ� ���ҽ� ����
		// ����(Buffer) - �޸� ���
		D3D11_BUFFER_DESC indexBufferDesc = { };
		indexBufferDesc.ByteWidth = sizeof(float) * 3 * 3;
		indexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = { };
		indexData.pSysMem = indices;

		// (�ε���) ���� ����
		result = device->CreateBuffer(&indexBufferDesc, &indexData, &vertexBuffer);

		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create index buffer. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// ���̴� ������
		ID3DBlob* vertexShaderBuffer = nullptr;
		result = D3DCompileFromFile(TEXT("VertexShader.hlsl"), nullptr, /*���̴� �ȿ� �ٸ� ���� ���Խ�Ű�°� ������ */nullptr, "main", "vs_5_0", 0, 0,&vertexShaderBuffer, nullptr);
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to compile vertex shader. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// ���̴� ����
		result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &vertexShader);
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
			}
		};
		// DX�� ���÷��� �ϴ°� ����
		result = device->CreateInputLayout(inputDesc, 1, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputlayout);
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create input layout. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// �ȼ� ���̴� ������/����
		// �� ���ҽ� ���ε�.
	}

	Renderer::~Renderer()
	{
	}
	void Renderer::Draw()
	{
		// �׸��� �� �۾� (BeginScene)
		// �����(Clear)
		float color[] = { 0.5647f, 0.6196f, 0.9529f };
		context->ClearRenderTargetView(renderTargetView, color);
		

		// ��ο�(Draw) (Draw)
		
		// ���� ��ȯ (EndScene/Present)
		swapChain->Present(1u, 0u);
	}
}