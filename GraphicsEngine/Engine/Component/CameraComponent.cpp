#include "CameraComponent.h"
#include "Core/Engine.h"
#include "Core/Common.h"
#include "Math/Matrix4.h"
#include "Actor/Actor.h"
#include "Core/InputController.h"


namespace GE
{
	CameraComponent::CameraComponent()
	{
		// 뷰행렬 업데이트 및 바인딩.
		/*data.viewMatrix
			= Matrix4::Translation(owner->transform.position * -1.0f)
			* Matrix4::Transpose(Matrix4::Rotation(owner->transform.rotation));*/

		// 행렬 전치.
		data.viewMatrix = Matrix4::Transpose(data.viewMatrix);

		// 데이터 담아서 버퍼 생성.
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(CameraBuffer);
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		// 버퍼 데이터.
		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &data;

		// 버퍼 생성.
		ID3D11Device& device = Engine::Get().Device();
		ThrowIfFailed(
			device.CreateBuffer(&bufferDesc, &bufferData, &cameraBuffer),
			TEXT("Failed to create camera buffer."));
	}

	CameraComponent::~CameraComponent()
	{
	}

	void CameraComponent::Tick(float deltaTime)
	{
		Component::Tick(deltaTime);

		// 입력 관리자 포인터 저장
		static InputController& input = InputController::Get();
		// 입력 테스트
		if (InputController::Get().IsKeyDown(VK_ESCAPE))
		{
			// 팝업창 띄위기
			if (MessageBox(nullptr, TEXT("Want to Quit?"), TEXT("Quit Engine"), MB_YESNO) == IDYES)
			{
				Engine::Get().Quit();
			}
		}

		// 카메라 이동 처리

		// 왼쪽 이동
		if (input.IsKey('A') || input.IsKey(VK_LEFT))
		{
			owner->transform.position.x -= 1.0f * deltaTime;
		}

		// 오른쪽 이동
		if (input.IsKey('D') || input.IsKey(VK_RIGHT))
		{
			owner->transform.position.x += 1.0f * deltaTime;
		}

		// 위쪽 이동
		if (input.IsKey('W') || input.IsKey(VK_UP))
		{
			owner->transform.position.y += 1.0f * deltaTime;
		}

		// 아래쪽 이동
		if (input.IsKey('S') || input.IsKey(VK_DOWN))
		{
			owner->transform.position.y -= 1.0f * deltaTime;
		}
	}

	void CameraComponent::Draw()
	{
		Component::Draw();

		// 뷰 행렬 업데이트 및 바인딩
		data.viewMatrix =
			Matrix4::Translation(owner->transform.position * (-1.0f)) *
			Matrix4::Transpose(Matrix4::Rotation(owner->transform.rotation));


		//
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 전치 행렬 (CPU와 GPU가 행렬을 다루는 방식이 달라서).
		// 행기준 행렬을 열 기준 행렬로 변환하기 위해 전치행렬 처리 -> 이게 GPU가 좋아하는 방식

		data.viewMatrix = Matrix4::Transpose(data.viewMatrix);

		// 버퍼 업데이트
		D3D11_MAPPED_SUBRESOURCE resource = {};

		// CPU가 데이터 작성중에는 GPU에게 읽지말라고 락을 걸음
		context.Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

		//resource.pData = &transformMatrix;
		// 복사
		memcpy(resource.pData, &data, sizeof(CameraBuffer));
		// 락 풀기
		context.Unmap(cameraBuffer, 0);

		// 버퍼 바인딩
		// 어떤 슬롯을 사용할건지 알려주는것
		context.VSSetConstantBuffers(1, 1, &cameraBuffer);
	}
}