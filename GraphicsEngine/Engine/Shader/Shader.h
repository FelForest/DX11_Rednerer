#pragma once
// 이게 머터리얼임
#include <string>
#include <d3d11.h>
namespace GE
{
	//RHI
	class RHI
	{
	public:
		virtual void Bind() = 0;
	};
	// 이걸 추상층 쓰면 됨

	class Shader
	{
	public:
		Shader(const std::wstring& name = L"Default");
		virtual ~Shader();

		// GPU에 쉐이더 객체를 연결(바인딩) 하는 함수
		void Bind();
	protected:
		// 쉐이더 파일 이름
		std::wstring name;

		// DX 리소스
		ID3D11InputLayout* inputlayout = nullptr;

		ID3D11VertexShader* vertexShader = nullptr;
		ID3DBlob* vertexShaderBuffer = nullptr;

		ID3D11PixelShader* pixelShader = nullptr;
		ID3DBlob* pixelShaderBuffer = nullptr;


	};
}