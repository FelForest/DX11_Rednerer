#include "Core//Engine.h"
#include <iostream>

#include "Math/Vector2.h"

// 메시지 : GUI에서 사용하는 이벤트 처리 방식
// 창에 관련된 메시지(이벤트)를 처리하는 콜백 함수.
LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
{
    // 메시지 처리
    switch (message)
    {
    // 창이 삭제되면 실행됨.
    case WM_DESTROY:
        // 이떄 프로그램 종료 메시지를 발생
        PostQuitMessage(0);
        return 0;

    // 창의 크기가 변경되면 실행
    case WM_SIZE:

        int width = LOWORD(lparam);
        int height = HIWORD(lparam);

        return 0;
    }
    // 기본 메시지 처리
    return DefWindowProc(handle, message, wparam, lparam);
}

using namespace GE;

/*
// 창 모드 할때 메시지 처리
int WINAPI WinMain(
    // 옵션 처리하는 값임 _IN_ 이런거
    // Handle Instance : 구조체임 
    _In_ HINSTANCE hInstance,
    // Window 3.1 버전 호환은 위한 것
    _In_opt_ HINSTANCE hPrevInstance,
    // 파라미터 옵션
    _In_ LPSTR lpCmdLine,
    // 옵션값
    _In_ int nShowCmd
)
{
    // 엔진 생성 및 실행
    Engine engine(1280, 800, TEXT("ENGINE DEMO"), hInstance);

    engine.Run();
    return 0;
}
*/

int main()
{
    // 엔진 생성 및 실행
    Engine engine(1280, 800, TEXT("ENGINE DEMO"), GetModuleHandle(nullptr));
    engine.Run();

}