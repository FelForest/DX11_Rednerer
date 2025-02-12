#include "Core//Engine.h"
#include <iostream>

#include "Math/Vector2.h"

// �޽��� : GUI���� ����ϴ� �̺�Ʈ ó�� ���
// â�� ���õ� �޽���(�̺�Ʈ)�� ó���ϴ� �ݹ� �Լ�.
LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
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

using namespace GE;

/*
// â ��� �Ҷ� �޽��� ó��
int WINAPI WinMain(
    // �ɼ� ó���ϴ� ���� _IN_ �̷���
    // Handle Instance : ����ü�� 
    _In_ HINSTANCE hInstance,
    // Window 3.1 ���� ȣȯ�� ���� ��
    _In_opt_ HINSTANCE hPrevInstance,
    // �Ķ���� �ɼ�
    _In_ LPSTR lpCmdLine,
    // �ɼǰ�
    _In_ int nShowCmd
)
{
    // ���� ���� �� ����
    Engine engine(1280, 800, TEXT("ENGINE DEMO"), hInstance);

    engine.Run();
    return 0;
}
*/

int main()
{
    // ���� ���� �� ����
    Engine engine(1280, 800, TEXT("ENGINE DEMO"), GetModuleHandle(nullptr));
    engine.Run();

}