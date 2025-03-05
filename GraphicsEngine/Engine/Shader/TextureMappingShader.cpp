#include "TextureMappingShader.h"
#include "Render/Texture.h"
#include "Resource/TextureLoader.h"

namespace GE
{
    TextureMappingShader::TextureMappingShader()
        : Shader(L"TextureMapping")
    {
    }
    TextureMappingShader::TextureMappingShader(const std::string& textureName) 
        : Shader(L"TextureMapping")
    {
        //texture = std::make_unique<Texture>(textureName);
        TextureLoader::Get().Load(textureName, texture);
    }
    void TextureMappingShader::Bind()
    {
        Shader::Bind();

        if (texture.lock())
        {
            texture.lock()->Bind();
        }
    }
}