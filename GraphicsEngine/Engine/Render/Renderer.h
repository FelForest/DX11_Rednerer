#pragma once

// DirectX11 ���.
#include <d3d11.h>
#include <dxgi.h>
#include <memory>

#include "../Core/Type.h"


namespace GE
{
	class Shader;
	// �׷���ī�忡�� ó���ϴ� ��/���ҽ��� �����ϴ� Ŭ����
	// RHI - Render Hardware Interface
	class Renderer
	{

		// ���� Ŭ���� friend ����
		friend class Engine;

	public:
		Renderer(uint32 width, uint32 height, HWND window);
		~Renderer();

		// �׸��� �Լ�
		void Draw(/*�� �ѱ� ����*/);

	private:
		// ���ҽ�
		// ��ġ��
		// ����
		ID3D11Device* device = nullptr;
		// �׸���
		ID3D11DeviceContext* context = nullptr;
		// ���� - �� ����Ʈ ��� ����
		IDXGISwapChain* swapChain = nullptr;

		// ����
		ID3D11RenderTargetView* renderTargetView = nullptr;

		// ����Ʈ
		D3D11_VIEWPORT viewport;

		// @Temp: �ӽ�.
// ���� ���� (���� ������ �����ϴ� �� �����).
		ID3D11Buffer* vertexBuffer = nullptr;

		// �ε��� ���� (������ ������ �� ������ ������ ����).
		ID3D11Buffer* indexBuffer = nullptr;

		std::unique_ptr<class TriangleMesh> Tmesh;
		std::unique_ptr<class QuardMesh> Qmesh;

		// ���̴� ��ü.
		std::unique_ptr<class Shader> shader;
	};
}