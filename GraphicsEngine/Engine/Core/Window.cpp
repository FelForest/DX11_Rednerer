#include "Window.h"

namespace GE
{
	Window::Window(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance, WNDPROC messageProcedure)
        : width(width), height(height), title(title), instance(instance), className(TEXT("Sample"))
	{
        // TEXT�� �����ڵ忡 ���� ��ũ���� : ���� �Ӽ����� �����ڵ����Ѵٰ� ������
        // ���ڿ� �ϳ� �ٲٴµ� ���� ���� ����

        // â ������ �ʿ��� ���� ����ü.
        WNDCLASS wc = { }; // �⺻�� ���� ���� 0��

        // �޽��� ó���� ���� �ݹ� ����
        wc.lpfnWndProc = messageProcedure;

        // ���α׷� �ּ� ����
        wc.hInstance = instance;

        // â ������ ����� Ŭ���� �̸� ����
        wc.lpszClassName = className.c_str();

        // Ŭ���� ���
        if (!RegisterClass(&wc))
        {
            // ���� �޽��� Ȯ��.
            //auto error = GetLastError();

            // �޽��� ���.
            // std::cout ����
            // 1��� - ���â(Output)�� �̿�
            OutputDebugStringW(TEXT("Failed to register a window class\n"));

            // 2��� - �޽��� �ڽ� �̿�
            MessageBox(nullptr, TEXT("Failed to register a window"), TEXT("Error"), MB_OK);

            // �ߴ��� ����
            __debugbreak();
        }

        // â�� ũ��
        // Ÿ��Ʋ�� ������ �������� ������ ������ ���� �ؾ� �ϱ� ������ ����

        // ȭ�� ���� ��ġ ����
        unsigned int positionX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
        unsigned int positionY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

        // â ũ�� ����
        RECT rect = { 0, 0, (long)width, (long)height };
        // ����ó�� ������� - ������ ���Ͼ� ��
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

        // â ũ�� �缳��
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

        // ���н� �����ڽ�
        if (handle == nullptr)
        {
            // �޽��� ���.
            // std::cout ����
            // 1��� - ���â(Output)�� �̿�
            OutputDebugString(TEXT("Failed to create a window class\n"));

            // 2��� - �޽��� �ڽ� �̿�
            MessageBox(nullptr, TEXT("Failed to create a window"), TEXT("Error"), MB_OK);

            // �ߴ��� ����
            __debugbreak();
        }

        // â ���̱� 
        // �ڿ� �ɼ� ã�ƺ���
        ShowWindow(handle, SW_SHOW);

        // â �޽��� ������Ʈ
        UpdateWindow(handle);
	}
	Window::~Window()
	{
        // Ŭ���� ��� ����
        UnregisterClass(className.c_str(), instance);
	}
	void Window::SetWidthHeight(uint32 width, uint32 height)
	{
        this->width = width;
        this->height = height;
	}
}