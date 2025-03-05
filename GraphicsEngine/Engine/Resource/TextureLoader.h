#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace GE
{
	class Texture;
	class TextureLoader
	{
	public:
		TextureLoader();
		~TextureLoader() = default;

		
		void Load(const std::string& name, std::weak_ptr<Texture>& outTexture);
		static TextureLoader& Get();

	private:
		static TextureLoader* instance;
		std::unordered_map < std::string, std::shared_ptr<class Texture >> textures;
	};
}
