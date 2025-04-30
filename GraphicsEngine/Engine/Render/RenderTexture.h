#pragma once

#include "Texture.h"
#include "Core/Type.h"
#include <d3d11.h>


namespace GE
{
	class RenderTexture : public Texture
	{
	public:
		RenderTexture(uint32 width = 0, uint32 height = 0);
		virtual ~RenderTexture();

		// RenderTargetView
		ID3D11RenderTargetView* GetRenderTarget() const { return renderTargetView; }

		ID3D11RenderTargetView** GetRenderTargetAddress()
		{
			return &renderTargetView;
		}

		ID3D11DepthStencilView* GetDepthStencilView() const
		{
			return depthStencilView;
		}
	private:
		ID3D11RenderTargetView* renderTargetView = nullptr;
		ID3D11DepthStencilView* depthStencilView = nullptr;
	};
}
