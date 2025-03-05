#include "Shader.h"
#include <d3dcompiler.h>
#include "../Core/Engine.h"
#include "DefaultShader.h"

namespace GE
{
	DefaultShader::DefaultShader(const std::wstring& name)
		: Shader(TEXT("Default"))
	{
	}
}