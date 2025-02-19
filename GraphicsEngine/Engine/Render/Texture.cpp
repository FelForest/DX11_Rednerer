#include "Texture.h"
#include "Core/Engine.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "Library/stbi_image.h"

namespace GE
{
	Texture::Texture()
	{
	}

	Texture::Texture(const std::string& name, BindType bindType, uint32 index)
		: name(name), bindType(bindType), index(index)
	{
        LoadTexture(name);
 	}

	Texture::~Texture()
	{
	}

    void Texture::Bind()
    {
        // 예외 처리.
        if (!textureData)
        {
            return;
        }

        // 컨텍스트 얻기.
        static ID3D11DeviceContext& context = Engine::Get().Context();

        // 바인딩.
        if (bindType == BindType::VertexShader)
        {
            context.VSSetShaderResources(index, 1, &textureData->shaderResourceView);
            context.VSSetSamplers(index, 1, &textureData->samplerState);
        }
        else if (bindType == BindType::PixelShader)
        {
            context.PSSetShaderResources(index, 1, &textureData->shaderResourceView);
            context.PSSetSamplers(index, 1, &textureData->samplerState);
        }
    }

	void Texture::LoadTexture(const std::string& name)
	{
        // 이미지 로드.
        // 경로 설정.
        char path[256] = {};
        sprintf_s(path, 256, "../Assets/Textures/%s", name.c_str());

        // 객체 생성.
        textureData = std::make_unique<TextureData>();

        // 이미지 파일 로드.
        textureData->data = stbi_load(path, &textureData->width, &textureData->height, &textureData->channelCount, 0);

        // 예외처리
        if (!textureData->data)
        {
            std::cout << "Error: Fail to load texture file: " << name << " \n";
            __debugbreak();
        }

        // DX 리소스 생성
        // 장치
        // 이렇게 받아오는거 별로 안좋아함 그냥 전역으로 냅두는 경우가 많음
        // 이 구현에서는 엔진에 다 넣어 놔서 상관 없음
        static ID3D11Device& device = Engine::Get().Device();

        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        textureDesc.ArraySize = 1;
        textureDesc.MipLevels = 1;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        textureDesc.Width = textureData->width;
        textureDesc.Height = textureData->height;

        D3D11_SUBRESOURCE_DATA data = {};
        data.pSysMem = textureData->data;
        data.SysMemPitch = textureData->width * textureData->channelCount;

        ID3D11Texture2D* texture = nullptr;
        auto result = device.CreateTexture2D(&textureDesc, &data, &texture);
        if (FAILED(result))
        {
            std::cout << "Error: Failed to create texture2d. \n";
            __debugbreak();
        }

        // 셰이더 리소스 뷰 생성(셰이더에 바인딩할 리소스)
        result = device.CreateShaderResourceView(texture, nullptr, &textureData->shaderResourceView);

        if (FAILED(result))
        {
            std::cout << "Error: Failed to create shaderResourceView. \n";
            __debugbreak();
        }

        // 다쓴 리소스 해제
        if (texture)
        {
            texture->Release();;
            texture = nullptr;
        }
        
        
        // 원래는 모든 타입을 만들어야 하지만 여기서는 한계점을 알고 제한해서 작성하면 괜찮을거 같음


        // 샘플러 데스트 내부 
        /*
        D3D11_FILTER Filter;
        D3D11_TEXTURE_ADDRESS_MODE AddressU;
        D3D11_TEXTURE_ADDRESS_MODE AddressV;
        D3D11_TEXTURE_ADDRESS_MODE AddressW;
        FLOAT MipLODBias;
        UINT MaxAnisotropy;
        D3D11_COMPARISON_FUNC ComparisonFunc;
        FLOAT BorderColor[ 4 ];
        FLOAT MinLOD;
        FLOAT MaxLOD;
        */

        D3D11_SAMPLER_DESC sampleDesc = {};
        sampleDesc.Filter = D3D11_FILTER_ANISOTROPIC;
        sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampleDesc.MaxLOD = FLT_MAX;
        sampleDesc.MinLOD = -FLT_MAX;
        sampleDesc.MaxAnisotropy = 3;
        sampleDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

        // 샘플러 생성
        result = device.CreateSamplerState(&sampleDesc, &textureData->samplerState);

        if (FAILED(result))
        {
            std::cout << "Error: Failed to create shaderResourceView. \n";
            __debugbreak();
        }

	}
}