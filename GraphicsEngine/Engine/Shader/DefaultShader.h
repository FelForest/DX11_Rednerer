#pragma once
// �̰� ���͸�����
#include <string>
#include <d3d11.h>
#include "Shader/Shader.h"

namespace GE
{

	class DefaultShader : public Shader
	{
	public:
		DefaultShader(const std::wstring& name = L"Default");
	};
}