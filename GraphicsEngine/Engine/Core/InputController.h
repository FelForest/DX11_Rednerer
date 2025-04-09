#pragma once

// 마우스 위치 좌표를 받아오기 위함 
#include "Math/Vector2.h"




// 입력 처리를 담당하는 클래스
namespace GE
{
	// 키입력 처리를 위한 구조체
	struct KeyInputData
	{
		// 입력 관련 변수
		bool isKeyDown = false;
		bool isKeyUp = false;
		bool isKey = false;

		// 키 값 설정 함수
		void SetKeyUpDown(bool isKeyUp, bool isKeyDown)
		{
			this->isKeyUp = isKeyUp;
			this->isKeyDown = isKeyDown;

			isKey = isKeyDown && !isKeyUp;
		}
	};

	// 마우스 입력 처리를 위한 구조체

	struct MouseInputData
	{
		// 마우스
		bool isButtonDown = false;
		bool isButtonUp = false;
		bool isButton = false;

		// 키 값 설정 함수
		void SetButtonUpDown(bool isButtonUp, bool isButtonDown)
		{
			this->isButtonUp = isButtonUp;
			this->isButtonDown = isButtonDown;

			isButton = isButtonDown && !isButtonUp;
		}

	};

	// 입력 관리자 클래스
	class InputController
	{
	public:
		InputController();
		~InputController();

		// 편의 함수
		bool IsKeyDown(unsigned int KeyCode);
		bool IsKeyUp(unsigned int KeyCode);
		bool IsKey(unsigned int KeyCode);

		bool IsButtonDown(unsigned int ButtonCode);
		bool IsButtonUp(unsigned int ButtonCode);
		bool IsButton(unsigned int ButtonCode);

		// 입력 정리 함수
		void ResetInputs();

		Vector2 GetMouserPosition();

		// 이전 프레임대비 이돈한 거리
		Vector2 GetMouseDelta();

		// 설정 함수
		void SetKeyUpDown(unsigned int keyCode, bool isKeyUp, bool isKeyDown);
		void SetButtonUpDown(unsigned int button, bool isButtonUp, bool isButtonDown);
		void SetMousePosition(int x, int y);

		// 싱글톤 접근 함수
		// 접근할 때 싱글톤이 초기화가 되어 있어 접근해도 문제가 없는지 항상 고민하도록! -> 너 실제로 당했음
		static InputController& Get();

		// 생성 여부(유효성 판단)
		static bool IsValid();

	private:

		// 키 / 버튼 입력 관련 변수
		KeyInputData keyInputData[256];
		MouseInputData mouseInputData[3];

		// 마우스 위치 변수
		Vector2 mousePosition = Vector2::Zero;
		Vector2 mousePreviousPosition = Vector2::Zero;

		// 싱글톤 구현을 위한 변수
		static InputController* instance;
	};

}
