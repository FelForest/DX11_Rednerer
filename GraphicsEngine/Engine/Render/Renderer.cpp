#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>

#include "../Math/Vector3.h"
#include "../Shader/Shader.h"
#include "TriangleMesh.h"
#include "QuardMesh.h"


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
		HRESULT result = D3D11CreateDeviceAndSwapChain(
			nullptr, 
			D3D_DRIVER_TYPE_HARDWARE, 
			nullptr, 
			flag, 
			featureLevels, 
			_countof(featureLevels), 
			D3D11_SDK_VERSION, 
			&swapChainDesc, /*�����쿡 ���� �ǰ� ���� ��ũ�η� �Ȱ�*/ 
			&swapChain, 
			&device, 
			nullptr,
			&context
		);

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
	}

	Renderer::~Renderer()
	{
	}
	void Renderer::Draw()
	{
		if (Qmesh == nullptr)
		{
			// ���̴� ��ü ����
			Qmesh = std::make_unique<QuardMesh>();
		}
		// �׸��� �� �۾� (BeginScene)
		// �����(Clear)
		float color[] = { 0.5647f, 0.6196f, 0.9529f, 0.0f };
		context->ClearRenderTargetView(renderTargetView, color);
		

		// ��ο�(Draw) (Draw)
		Qmesh->Draw();

		// ���� ��ȯ (EndScene/Present)
		swapChain->Present(1u, 0u);
	}
	
}