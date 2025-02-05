#pragma once

#include <Windows.h>
#include <string>
#include "Type.h"

namespace GE
{
	// ������ Ŭ����
	class Window
	{
	public:
		Window(uint32 width, uint32 height, const std::wstring & title, HINSTANCE instance, WNDPROC messageProcedure);

		~Window();

		// Getter/Setter.
		inline const uint32 Width() const { return width; }
		inline const uint32 Height() const { return height; }
		inline HWND Handle() const { return handle; }

		void SetWidthHeight(uint32 width, uint32 height);

	private:
		uint32 width = 0;
		uint32 height = 0;

		std::wstring title = nullptr;
		std::wstring className = TEXT("Graphis Engine Class");

		HWND handle = nullptr;
		HINSTANCE instance = nullptr;
	};
}