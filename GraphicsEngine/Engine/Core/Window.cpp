#include "Window.h"

namespace GE
{
	Window::Window(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance, WNDPROC messageProcedure)
        : width(width), height(height), title(title), instance(instance), className(TEXT("Sample"))
	{
        // TEXT는 유니코드에 관한 메크로임 : 지금 속성에서 유니코드사용한다고 말했음
        // 문자열 하나 바꾸는데 많은 일이 있음

        // 창 생성에 필요한 설정 구조체.
        WNDCLASS wc = { }; // 기본값 구문 값이 0임

        // 메시지 처리를 위한 콜백 전달
        wc.lpfnWndProc = messageProcedure;

        // 프로그램 주소 전달
        wc.hInstance = instance;

        // 창 생성에 사용할 클래스 이름 전달
        wc.lpszClassName = className.c_str();

        // 클래스 등록
        if (!RegisterClass(&wc))
        {
            // 오류 메시지 확인.
            //auto error = GetLastError();

            // 메시지 출력.
            // std::cout 못씀
            // 1방법 - 출력창(Output)을 이용
            OutputDebugStringW(TEXT("Failed to register a window class\n"));

            // 2방법 - 메시지 박스 이용
            MessageBox(nullptr, TEXT("Failed to register a window"), TEXT("Error"), MB_OK);

            // 중단점 설정
            __debugbreak();
        }

        // 창의 크기
        // 타이틀바 같은게 있을때는 윈도우 사이즈 설정 해야 하기 때문에 힘듬

        // 화면 시작 위치 조정
        unsigned int positionX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
        unsigned int positionY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

        // 창 크기 조정
        RECT rect = { 0, 0, (long)width, (long)height };
        // 예외처리 해줘야함 - 보통은 안일어 남
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

        // 창 크기 재설정
        unsigned int windowWidth = rect.right - rect.left;
        unsigned int windowHeight = rect.bottom - rect.top;

        handle = CreateWindow(
            className.c_str(),              // Window class
            title.c_str(),                  // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            positionX, positionY, windowWidth, windowHeight,
            //CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            nullptr,       // Parent window    
            nullptr,       // Menu
            instance,  // Instance handle
            nullptr        // Additional application data
        );

        // 실패시 오류박스
        if (handle == nullptr)
        {
            // 메시지 출력.
            // std::cout 못씀
            // 1방법 - 출력창(Output)을 이용
            OutputDebugString(TEXT("Failed to create a window class\n"));

            // 2방법 - 메시지 박스 이용
            MessageBox(nullptr, TEXT("Failed to create a window"), TEXT("Error"), MB_OK);

            // 중단점 설정
            __debugbreak();
        }

        // 창 보이기 
        // 뒤에 옵션 찾아보기
        ShowWindow(handle, SW_SHOW);

        // 창 메시지 업데이트
        UpdateWindow(handle);
	}
	Window::~Window()
	{
        // 클래스 등록 해제
        UnregisterClass(className.c_str(), instance);
	}
	void Window::SetWidthHeight(uint32 width, uint32 height)
	{
        this->width = width;
        this->height = height;
	}
}