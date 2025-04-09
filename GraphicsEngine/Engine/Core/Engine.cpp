﻿#include "Engine.h"
#include "Window.h"
#include "../Render/Renderer.h"
#include "Resource/ShaderLoader.h"
#include "Resource/TextureLoader.h"
#include "Resource/ModelLoader.h"
#include "InputController.h"

#include "Level/Level.h"

#include <iostream>

namespace GE
{
	// 싱글톤 객체 설정
	Engine* Engine::instance = nullptr;

	Engine::Engine(uint32 width, uint32 height, const std::wstring& title, HINSTANCE hInstance)
	{
		// 싱글톤 객체 값 설정
		instance = this;

		// 인풋 컨트롤러 객체 생성
		inputController = std::make_unique<InputController>();

		// 창 객체 생성
		window = std::make_shared<Window>(width, height, title, hInstance, WindowProc);

		// 셰이더 로더 객체 생성
		shaderLoader = std::make_unique<ShaderLoader>();

		// 텍스처 로더 객체 생성
		textureLoader = std::make_unique<TextureLoader>();

		// 모델 로더 객체 생성
		modelLoader = std::make_unique<ModelLoader>();

		// 랜더러 생성
		renderer = std::make_shared<Renderer>(width, height, window->Handle());
	}

	Engine::~Engine()
	{
	}
	void Engine::Run()
	{
		// 타이머.
		LARGE_INTEGER currentTime;
		LARGE_INTEGER previousTime;
		LARGE_INTEGER frequency;

		// 하드웨어 타이머의 해상도 값(기준 단위)
		QueryPerformanceFrequency(&frequency);

		// 현재 시간
		QueryPerformanceCounter(&currentTime);
		previousTime = currentTime;

		// 프레임 계산에 사용할 변수
		float targetFrameRate = 120.0f;
		// 고정 프레임 속도를 사용하기 위한 벽수
		float oneFrameTime = 1.0f / targetFrameRate;



		// 메시지 처리 루프
		MSG msg = { };
		// PeekMessage 입력 받으면 true 값을 반환 하고 아니면 false값을 반환해서 계속 돌기 위한거
		// GetMessage 사용 안하는 이유 : 메시지가 들어올때까지 대기해서 engine에는 부적합함
		while (msg.message != WM_QUIT) // WM_QUIT WM_DESTROY
		{
			// 엦니 종료 처리
			if (isQuit)
			{
				break;
			}
			// 창에 메시지가 들어올때 실행
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				// 메시지 번역
				TranslateMessage(&msg);

				// 메시지 전달
				DispatchMessage(&msg);
			}

			// 창에 메시지가 없으면 다른 작업 처리
			else
			{
				// 현재 시간 가져오기
				QueryPerformanceCounter(&currentTime);

				// 프레임 시간 계산
				float deltaTime = (float)(currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;

				// 프레임 제한
				if (deltaTime >= oneFrameTime)
				{
					// 출력
					std::cout << "DeltaTime : " << deltaTime << " | OneFrameTime : " << oneFrameTime << " | FPS : " << (int)ceil(1.0f / deltaTime) << "\n";

					// 창 제목에 출력을 위한 문자열 생성
					wchar_t stat[512] = {};
					swprintf_s(stat, 512, TEXT("[%s] - [DeltaTime: %f] [FPS : %d]"), window->Title().c_str(), deltaTime, static_cast<int>(ceil(1.0f / deltaTime)));
					// 창 제목에 출력
					SetWindowText(window->Handle(), stat);
					// 엔진 루프.
				// 레벨 처리
					if (mainLevel)
					{
						mainLevel->BeginPlay();
						mainLevel->Tick(deltaTime);
						renderer->Draw(mainLevel);
					}

					// 프레임 시간 업데이트
					previousTime = currentTime;

					// 입력 초기화
					inputController->ResetInputs();
				}

				
			}
		}
	}

	void Engine::SetLevle(std::shared_ptr<Level> newLevel)
	{
		// 메인 레벨 설정
		mainLevel = newLevel;
	}

	LRESULT Engine::WindowProc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		// 입력 관리자가 준비 안됐으면 종료
		if (!InputController::Get().IsValid())
		{
			return DefWindowProc(handle, message, wparam, lparam);
		}

		// 메시지 처리
		switch (message)
		{
			// 창이 삭제되면 실행됨.
		case WM_DESTROY:
			// 이떄 프로그램 종료 메시지를 발생
			//PostQuitMessage(0);

			Engine::Get().Quit();
			break;

		case WM_LBUTTONDOWN:
		{
			InputController::Get().SetButtonUpDown(0, false, true);
		}
		break;

		case WM_LBUTTONUP:
		{
			InputController::Get().SetButtonUpDown(0, true, false);
		}
		break;

		case WM_RBUTTONDOWN:
		{
			InputController::Get().SetButtonUpDown(1, false, true);
		break;
		}

		case WM_RBUTTONUP:
		{
			InputController::Get().SetButtonUpDown(1, true, false);
		}
		break;

		case WM_MBUTTONDOWN:
		{
			InputController::Get().SetButtonUpDown(2, false, true);
		}
		break;

		case WM_MBUTTONUP:
		{
			InputController::Get().SetButtonUpDown(2, true, false);
		}
		break;

		case WM_MOUSEMOVE:
		{
			// 현재 마우스 위치값 받아오기
			int xPosition = LOWORD(lparam);
			int yPosition = HIWORD(lparam);

			InputController::Get().SetMousePosition(xPosition, yPosition);
		}
		break;

		case WM_SIZE:
		{
			if (wparam == SIZE_MINIMIZED)
			{
				break;
			}

			uint32 width = static_cast<uint32>(LOWORD(lparam));
			uint32 height = static_cast<uint32>(HIWORD(lparam));

			// 가로 / 세로 크기 값 전달.
			Engine::Get().OnResize(width, height);
		}
		break;

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			// MSDN 문서를 확인해 보면, 30번째 비트는 KeyUp 상태를 나타낸다고 나옴.
			bool isKeyUp = ((lparam & (static_cast<long long>(1) << 30)) != 0);

			// MSDN 문서를 확인해 보면, 31번째 비트는 KeyDown 상태를 나타낸다고 나옴.
			bool isKeyDown = ((lparam & (static_cast<long long>(1) << 31)) == 0);

			// 엔진에 키 입력 데이터 전달.
			if (isKeyUp != isKeyDown)
			{
				// 가상 키 값.
				uint32 vkCode = static_cast<uint32>(wparam);
				InputController::Get().SetKeyUpDown(vkCode, isKeyUp, isKeyDown);
			}
		} 
		break;
		}	
		// 기본 메시지 처리
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

	// 게임 최적화 할때 크기 제한해 두는 것도 있음
	void Engine::OnResize(uint32 width, uint32 height)
	{
		if (!window)
		{
			return;
		}

		if (!renderer)
		{
			return;
		}

		// 윈도우 클래스의 크기 조정
		window->SetWidthHeight(width, height);

		RECT rect;
		GetClientRect(window->Handle(), &rect);

		uint32 w = static_cast<uint32>(rect.right - rect.left);
		uint32 h = static_cast<uint32>(rect.bottom - rect.top);

		renderer->OnResize(w, h);
	}
	void Engine::Quit()
	{
		isQuit = true;
	}
}