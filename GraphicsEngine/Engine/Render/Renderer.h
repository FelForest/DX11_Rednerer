#pragma once

// DirectX11 헤더.
#include <d3d11.h>
#include <dxgi.h>
#include <memory>

#include "../Core/Type.h"


namespace GE
{
	class Shader;
	// 그래픽카드에서 처리하는 일/리소스를 관리하는 클래스
	// RHI - Render Hardware Interface
	class Renderer
	{

		// 엔진 클래스 friend 선언
		friend class Engine;

	public:
		Renderer(uint32 width, uint32 height, HWND window);
		~Renderer();

		// 그리기 함수
		void Draw(std::shared_ptr<class Level> level);

	private:
		// 리소스
		// 장치류
		// 생성
		ID3D11Device* device = nullptr;
		// 그리기
		ID3D11DeviceContext* context = nullptr;
		// 스왑 - 백 프론트 출력 관련
		IDXGISwapChain* swapChain = nullptr;

		// 버퍼
		ID3D11RenderTargetView* renderTargetView = nullptr;

		// 뷰포트
		D3D11_VIEWPORT viewport;
	};
}