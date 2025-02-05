#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>

namespace GE
{
	Renderer::Renderer(uint32 width, uint32 height, HWND window)
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
		swapChainDesc.BufferCount = 1;									

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
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


		// 장치 생성
		// 이건 할게 많은데 -> 여러가지 알 수 있음
		//D3D11CreateDevice;

		
		// 3개만 생성
		HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flag, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, /*윈도우에 통합 되고 나서 메크로로 된거*/ &swapChainDesc, &swapChain, &device, nullptr, &context);

		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create devices. "), TEXT("Error"), MB_OK);
			__debugbreak();
			
		}

		// 랜더 타겟 뷰 생성.
		ID3D11Texture2D* backbuffer = nullptr;

		// 버퍼 받아오기
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

		// 정점 데이터 생성
		float vertices[] =
		{
			 0.0f,  0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
		};

		// @Temp : 임시 리소스 생성
		// 버퍼(Buffer) - 메모리 덩어리
		D3D11_BUFFER_DESC vertexBufferDesc = { };
		vertexBufferDesc.ByteWidth = sizeof(float) * 3 * 3;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = { };
		vertexData.pSysMem = vertices;

		// (정점) 버퍼 생성
		result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create vertex buffer. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// 인덱스(색인) 버퍼 생성(정정 조립하는 순서)
		int indices[] =
		{
			0, 1, 2
		};

		// @Temp : 임시 리소스 생성
		// 버퍼(Buffer) - 메모리 덩어리
		D3D11_BUFFER_DESC indexBufferDesc = { };
		indexBufferDesc.ByteWidth = sizeof(float) * 3 * 3;
		indexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = { };
		indexData.pSysMem = indices;

		// (인덱스) 버퍼 생성
		result = device->CreateBuffer(&indexBufferDesc, &indexData, &vertexBuffer);

		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create index buffer. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// 쉐이더 컴파일
		ID3DBlob* vertexShaderBuffer = nullptr;
		result = D3DCompileFromFile(TEXT("VertexShader.hlsl"), nullptr, /*쉐이더 안에 다른 파일 포함시키는거 설정값 */nullptr, "main", "vs_5_0", 0, 0,&vertexShaderBuffer, nullptr);
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to compile vertex shader. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// 쉐이더 생성
		result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &vertexShader);
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
				0, 
				D3D11_INPUT_PER_VERTEX_DATA, 
				0 
			}
		};
		// DX에 리플렉션 하는게 있음
		result = device->CreateInputLayout(inputDesc, 1, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputlayout);
		if (FAILED(result))
		{
			MessageBox(nullptr, TEXT("Failed to create input layout. "), TEXT("Error"), MB_OK);
			__debugbreak();
		}

		// 픽셀 쉐이더 컴파일/생성
		// 각 리소스 바인딩.
	}

	Renderer::~Renderer()
	{
	}
	void Renderer::Draw()
	{
		// 그리기 전 작업 (BeginScene)
		// 지우기(Clear)
		float color[] = { 0.5647f, 0.6196f, 0.9529f };
		context->ClearRenderTargetView(renderTargetView, color);
		

		// 드로우(Draw) (Draw)
		
		// 버퍼 교환 (EndScene/Present)
		swapChain->Present(1u, 0u);
	}
}