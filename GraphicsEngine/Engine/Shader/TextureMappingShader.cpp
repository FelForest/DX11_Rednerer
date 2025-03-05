#include "TextureMappingShader.h"
#include "Render/Texture.h"
namespace GE
{
    TextureMappingShader::TextureMappingShader()
        : Shader(L"TextureMapping")
    {
    }
    TextureMappingShader::TextureMappingShader(const std::string& textureName) 
        : Shader(L"TextureMapping")
    {
        texture = std::make_unique<Texture>(textureName);
    }
    void TextureMappingShader::Bind()
    {
        Shader::Bind();

        if (texture)
        {
            texture->Bind();
        }
    }
}