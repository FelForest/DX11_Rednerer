#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>

#include "../Math/Vector3.h"
#include "../Shader/Shader.h"
#include "TriangleMesh.h"
#include "QuardMesh.h"
#include "Core/Common.h"

namespace GE
{
	Renderer::Renderer(uint32 width, uint32 height, /*어느창에 그려야 하나*/HWND window)
	{
		// 장치 생성에 사용하는 옵션
		uint32 flag = 0u;

#if _DEBUG
		// 디버그 생성을 더 해줌
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// 생성할 라이브러리 버전
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			// 시도해 보고 안되면 다음꺼 한다는 느낌
			// 최신 버전이 가장 위에 있는게 맞음
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		D3D_FEATURE_LEVEL outFeatureLevel;

		ThrowIfFailed(D3D11CreateDevice(
			nullptr, D3D_DRIVER_TYPE_HARDWARE,
			nullptr, flag, featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION, &device,
			/*무슨 버전 쓰는지 알려주는 것*/
			&outFeatureLevel,
			&context), TEXT("Failed to create devices."));

		// IDXGIFactory 리소스 생성
		IDXGIFactory* factory = nullptr;
		// 이게 정석
		//CreateDXGIFactory(__uuidof(factory), reinterpret_cast<void**>(&factory));

		ThrowIfFailed(CreateDXGIFactory(IID_PPV_ARGS(&factory)),
			TEXT("Failed to create dxgifactory"));

		// 스왑 체인 정보 구조체
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

		// 멜티 샘플링 지우너 여부 확인



		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		// 창 모드
		swapChainDesc.Windowed = true;									
		swapChainDesc.OutputWindow = window;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		// 백버퍼 개수
		swapChainDesc.BufferCount = 2;									

		// 에일리어싱 / 앨리어싱
		// 멀티 샘플링 갯수
		// 1개는 안쓴다는 뜻
		swapChainDesc.SampleDesc.Count = 1;		
		// 멀티 샘플링 수준
		swapChainDesc.SampleDesc.Quality = 0;							

		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// 버퍼 스왑 방법
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;


		// 장치 생성
		// 이건 할게 많은데 -> 여러가지 알 수 있음
		//D3D11CreateDevice;

		
		// 3개만 생성
		//ThrowIfFailed(D3D11CreateDeviceAndSwapChain(
		//	nullptr,
		//	D3D_DRIVER_TYPE_HARDWARE,
		//	nullptr,
		//	flag,
		//	featureLevels,
		//	_countof(featureLevels),
		//	D3D11_SDK_VERSION,
		//	&swapChainDesc, /*윈도우에 통합 되고 나서 메크로로 된거*/
		//	&swapChain,
		//	&device,
		//	nullptr,
		//	&context
		//), TEXT("Failed to create device"));

		/*if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create devices. "), TEXT("Error"), MB_OK);
			__debugbreak();
			
		}*/

		// SwapChain 생성
		ThrowIfFailed(factory->CreateSwapChain(
			device,
			&swapChainDesc,
			&swapChain
		), TEXT("Failed to create a swap chain."));

		// 랜더 타겟 뷰 생성.
		ID3D11Texture2D* backbuffer = nullptr;

		// 버퍼 받아오기
		//swapChain->GetBuffer(0, __uuidof(backbuffer), reinterpret_cast<void**>(&backbuffer));
		ThrowIfFailed(swapChain->GetBuffer(
			0, IID_PPV_ARGS(&backbuffer)
		), TEXT("Failed to get back buffer."));


		ThrowIfFailed(device->CreateRenderTargetView(
			backbuffer, nullptr, &renderTargetView
		), TEXT("Failed to create render target view."));

		// 랜더 타겟 뷰 바인딩(연결)
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);
		// 원래는 따로 오류 판정 해 줘야함 나중에 따로 해줘

		// 뷰 포트(화면)
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;

		// 뷰포트 설정
		context->RSSetViewports(1, &viewport);
	}

	Renderer::~Renderer()
	{
	}
	void Renderer::Draw()
	{
		if (Qmesh == nullptr)
		{
			// 쉐이더 객체 생성
			Qmesh = std::make_unique<QuardMesh>();
			// 이미 scale은 Vector3::One 인데 왜 그런걸까 
			//Qmesh->transform.scale = Vector3::One;
			Qmesh->transform.scale = Vector3::One * 0.5f;
			Qmesh->transform.position.x = 0.5f;
		}

		if (Qmesh2 == nullptr)
		{
			Qmesh2 = std::make_unique<QuardMesh>();
			Qmesh2->transform.scale = Vector3::One * 0.5f;
			Qmesh2->transform.position.x = -0.5f;
		}

		if (Tmesh == nullptr)
		{
			Tmesh = std::make_unique<TriangleMesh>();
			Tmesh->transform.scale = Vector3::One * 0.5f;
			Tmesh->transform.position.x = 0.0f;
			Tmesh->transform.position.y = 0.5f;
		}

		// 그리기 전 작업 (BeginScene)
		// 매번 타겟팅 해줘야함, 하지면 여기는 안바꿈
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);
		
		// 지우기(Clear)
		float color[] = { 0.5647f, 0.6196f, 0.9529f, 0.0f };
		context->ClearRenderTargetView(renderTargetView, color);
		
		// Test
		Qmesh->Update(1.0f / 60.0f);
		Qmesh2->Update(1.0f / 60.0f);

		// 드로우(Draw) (Draw)
		Qmesh->Draw();
		Qmesh2->Draw();
		Tmesh->Draw();

		// 버퍼 교환 (EndScene/Present)
		swapChain->Present(1u, 0u);
	}
	
}