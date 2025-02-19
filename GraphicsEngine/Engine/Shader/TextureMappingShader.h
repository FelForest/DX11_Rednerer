#pragma once

#include "Shader.h"

#include <memory>

#include "Render/Texture.h"

namespace GE
{
	class TextureMappingShader : public Shader
	{
	public:
		TextureMappingShader();
		TextureMappingShader(const std::string& textureName = "");

		virtual void Bind() override;

	private:
		// �ؽ�ó ���ҽ�
		std::unique_ptr<class Texture> texture;
	};
}