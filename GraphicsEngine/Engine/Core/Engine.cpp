#include "Engine.h"
#include "Window.h"
#include "../Render/Renderer.h"
#include "Resource/ShaderLoader.h"
#include "Resource/TextureLoader.h"
#include "Resource/ModelLoader.h"

#include "Level/Level.h"

#include <iostream>

namespace GE
{
	// �̱��� ��ü ����
	Engine* Engine::instance = nullptr;

	Engine::Engine(uint32 width, uint32 height, const std::wstring& title, HINSTANCE hInstance)
	{
		// �̱��� ��ü �� ����
		instance = this;

		// â ��ü ����
		window = std::make_shared<Window>(width, height, title, hInstance, WindowProc);

		// ���̴� �δ� ��ü ����
		shaderLoader = std::make_unique<ShaderLoader>();

		// �ؽ�ó �δ� ��ü ����
		textureLoader = std::make_unique<TextureLoader>();

		// �� �δ� ��ü ����
		modelLoader = std::make_unique<ModelLoader>();

		// ������ ����
		renderer = std::make_shared<Renderer>(width, height, window->Handle());
	}

	Engine::~Engine()
	{
	}
	void Engine::Run()
	{
		// Ÿ�̸�.
		LARGE_INTEGER currentTime;
		LARGE_INTEGER previousTime;
		LARGE_INTEGER frequency;

		// �ϵ���� Ÿ�̸��� �ػ� ��(���� ����)
		QueryPerformanceFrequency(&frequency);

		// ���� �ð�
		QueryPerformanceCounter(&currentTime);
		previousTime = currentTime;

		// ������ ��꿡 ����� ����
		float targetFrameRate = 120.0f;
		// ���� ������ �ӵ��� ����ϱ� ���� ����
		float oneFrameTime = 1.0f / targetFrameRate;



		// �޽��� ó�� ����
		MSG msg = { };
		// PeekMessage �Է� ������ true ���� ��ȯ �ϰ� �ƴϸ� false���� ��ȯ�ؼ� ��� ���� ���Ѱ�
		// GetMessage ��� ���ϴ� ���� : �޽����� ���ö����� ����ؼ� engine���� ��������
		while (msg.message != WM_QUIT) // WM_QUIT WM_DESTROY
		{
			// â�� �޽����� ���ö� ����
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				// �޽��� ����
				TranslateMessage(&msg);

				// �޽��� ����
				DispatchMessage(&msg);
			}

			// â�� �޽����� ������ �ٸ� �۾� ó��
			else
			{
				// ���� �ð� ��������
				QueryPerformanceCounter(&currentTime);

				// ������ �ð� ���
				float deltaTime = (float)(currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;

				// ������ ����
				if (deltaTime >= oneFrameTime)
				{
					// ���
					std::cout << "DetlaTime : " << deltaTime << " | OneFrameTime : " << oneFrameTime << " | FPS : " << (int)ceil(1.0f / deltaTime) << "\n";

					// ���� ����.
				// ���� ó��
					if (mainLevel)
					{
						mainLevel->BeginPlay();
						mainLevel->Tick(deltaTime);
						renderer->Draw(mainLevel);
					}

					// ������ �ð� ������Ʈ
					previousTime = currentTime;
				}

				
			}
		}
	}

	void Engine::SetLevle(std::shared_ptr<Level> newLevel)
	{
		// ���� ���� ����
		mainLevel = newLevel;
	}

	LRESULT Engine::WindowProc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		// �޽��� ó��
		switch (message)
		{
			// â�� �����Ǹ� �����.
		case WM_DESTROY:
			// �̋� ���α׷� ���� �޽����� �߻�
			PostQuitMessage(0);
			return 0;

			// â�� ũ�Ⱑ ����Ǹ� ����
		case WM_SIZE:

			int width = LOWORD(lparam);
			int height = HIWORD(lparam);

			return 0;
		}
		// �⺻ �޽��� ó��
		return DefWindowProc(handle, message, wparam, lparam);
	}

	Engine& Engine::Get()
	{
		return *instance;
	}

	ID3D11Device& Engine::Device() const
	{
		return *renderer->device;
	}

	ID3D11DeviceContext& Engine::Context() const
	{
		return *renderer->context;
	}
}