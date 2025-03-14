#pragma once

#include <memory>
#include <Windows.h>
#include <string>
#include "Type.h"
#include <d3d11.h>
namespace GE
{
	class Engine
	{
		// ����� ��ü ���ҽ��� �����ϵ��� ����
	public:
		Engine(uint32 width, uint32 height, const std::wstring& title, HINSTANCE hInstance);
		virtual ~Engine();


		// ���� ���� �Լ�
		void Run();

		// ������ �޽��� ó�� ����.
		static LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam);

		// �̱��� ���� �Լ�.
		static Engine& Get();

		// Render Getter
		ID3D11Device& Device() const;
		ID3D11DeviceContext& Context() const;

	protected:

		// â ��ü
		std::shared_ptr<class Window> window;

		// ������ ��ü
		std::shared_ptr<class Renderer> renderer;

		// ���̴� �δ� ��ü
		std::unique_ptr<class ShaderLoader> shaderLoader;

		// �ؽ�ó �δ� ����
		std::unique_ptr<class TextureLoader> textureLoader;

		// �� �δ� ����
		std::unique_ptr<class ModelLoader> modelLoader;

		// �̱��� ��ü
		static Engine* instance;
	};
}