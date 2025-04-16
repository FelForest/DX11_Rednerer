#include "CameraActor.h"
#include "Component/CameraComponent.h"
#include "Core/Engine.h"
#include "Core/InputController.h"

namespace GE
{
    CameraActor::CameraActor()
    {
        // 카메라 컴포넌트 추가
        AddComponent(std::make_shared<CameraComponent>());
    }

    

    void CameraActor::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        Move(deltaTime);

        Rotate();
    }

    void CameraActor::Move(float deltaTime)
    {
        // 입력 관리자 포인터 저장
        static InputController& input = InputController::Get();
        // 입력 테스트
        if (InputController::Get().IsKeyDown(VK_ESCAPE))
        {
            if (MessageBox(nullptr, TEXT("Want to Quit?"), TEXT("Quit Engine"), MB_YESNO) == IDYES)
            {
                Engine::Get().Quit();
            }
        }

        // 카메라 이동 처리

        // 카메라 이동 속력
        static const float moveSpeed = 1.0f;
        
        // 왼쪽 이동
        if (input.IsKey('A') || input.IsKey(VK_LEFT))
        {
            transform.position -= transform.Right() * moveSpeed * deltaTime;
        }

        // 오른쪽 이동
        if (input.IsKey('D') || input.IsKey(VK_RIGHT))
        {
            transform.position += transform.Right() * moveSpeed * deltaTime;
        }

        // 앞쪽 이동
        if (input.IsKey('W') || input.IsKey(VK_UP))
        {
            transform.position += transform.Forward() * moveSpeed * deltaTime;
        }

        // 뒤쪽 이동
        if (input.IsKey('S') || input.IsKey(VK_DOWN))
        {
            transform.position -= transform.Forward() * moveSpeed * deltaTime;
        }

        // 위쪽 이동
        if (input.IsKey('Q'))
        {
            transform.position -= transform.UP() * moveSpeed * deltaTime;
        }

        // 아래쪽 이동
        if (input.IsKey('E'))
        {
            transform.position += transform.UP() * moveSpeed * deltaTime;
        }
    }

    void CameraActor::Rotate()
    {
        // 입력 관리자 포인터 저장
        static InputController& input = InputController::Get();

        // 마우스 드래그 확인
        if (input.IsButton(0))
        {
            // 드래그 감도
            static float sensitivity = 0.05f;
            transform.rotation.x += input.GetMouseDelta().y * sensitivity;
            transform.rotation.y += input.GetMouseDelta().x * sensitivity;
        }
    }
}
