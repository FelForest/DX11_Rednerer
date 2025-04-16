#include "QuadActor.h"

#include "Component/StaticMeshComponent.h"
#include "Render/QuardMesh.h"
#include "Render/SphereMesh.h"
#include "Shader/TextureMappingShader.h"
#include "Resource/ShaderLoader.h"
#include "Resource/TextureLoader.h"
#include "Render/Texture.h"

namespace GE
{
	QuadActor::QuadActor()
	{
		std::shared_ptr<StaticMeshComponent> meshComponent = std::make_shared<StaticMeshComponent>();
		
		AddComponent(meshComponent);

		//meshComponent->SetMesh(std::make_shared<QuardMesh>());
		meshComponent->SetMesh(std::make_shared<SphereMesh>());

		std::weak_ptr<TextureMappingShader> shader;
		if (ShaderLoader::Get().Load<TextureMappingShader>(shader))
		{
			meshComponent->AddShader(shader);
		}

		// 텍스처 로드 및 셰이더에 설정
		std::weak_ptr<Texture> texture;
		TextureLoader::Get().Load("T_SuperMario.png", texture);
		shader.lock()->SetTexture(texture);
	}
}