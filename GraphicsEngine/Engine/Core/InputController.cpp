#include "InputController.h"

namespace GE
{
	// static 변수 정의
	InputController* InputController::instance = nullptr;

	InputController::InputController()
	{
		// 싱글톤 만들고 제발 넣어줘
		instance = this;
	}

	// 스마트 포인터 대상일때는 default가 오류 뜨는 경우가 있으므로 만드는게 좋음
	InputController::~InputController()
	{
	}

	bool InputController::IsKeyDown(unsigned int KeyCode)
	{
		return keyInputData[KeyCode].isKeyDown;
	}

	bool InputController::IsKeyUp(unsigned int KeyCode)
	{
		return keyInputData[KeyCode].isKeyUp;
	}

	bool InputController::IsKey(unsigned int KeyCode)
	{
		return keyInputData[KeyCode].isKey;
	}

	bool InputController::IsButtonDown(unsigned int ButtonCode)
	{
		return mouseInputData[ButtonCode].isButtonDown;
	}

	bool InputController::IsButtonUp(unsigned int ButtonCode)
	{
		return mouseInputData[ButtonCode].isButtonUp;
	}

	bool InputController::IsButton(unsigned int ButtonCode)
	{
		return mouseInputData[ButtonCode].isButton;
	}

	void InputController::ResetInputs()
	{
		for (KeyInputData& data : keyInputData)
		{
			data.isKeyUp = false;
			data.isKeyDown = false;
		}

		for (MouseInputData& data : mouseInputData)
		{
			data.isButtonDown = false;
			data.isButtonUp = false;
		}

		mousePreviousPosition = mousePosition;
	}

	Vector2 InputController::GetMouserPosition()
	{
		return mousePosition;
	}

	Vector2 InputController::GetMouseDelta()
	{
		return Vector2(static_cast<float>(mousePosition.x - mousePreviousPosition.x), static_cast<float>(mousePosition.y - mousePreviousPosition.y));
	}

	void InputController::SetKeyUpDown(unsigned int keyCode, bool isKeyUp, bool isKeyDown)
	{
		keyInputData[keyCode].SetKeyUpDown(isKeyUp, isKeyDown);
	}

	void InputController::SetButtonUpDown(unsigned int button, bool isButtonUp, bool isButtonDown)
	{
		mouseInputData[button].SetButtonUpDown(isButtonUp, isButtonDown);
	}

	void InputController::SetMousePosition(int x, int y)
	{
		mousePreviousPosition = mousePosition;
		mousePosition = Vector2((float)x, (float)y);
	}

	InputController& InputController::Get()
	{
		return *instance;
	}
	bool InputController::IsValid()
	{
		return instance != nullptr;
	}
}