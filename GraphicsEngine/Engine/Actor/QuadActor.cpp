#include "QuadActor.h"

#include "Component/StaticMeshComponent.h"
#include "Render/QuardMesh.h"
#include "Shader/TextureMappingShader.h"
#include "Resource/ShaderLoader.h"
#include "Resource/TextureLoader.h"
#include "Render/Texture.h"
#include "Shader/NormalMappingShader.h"
#include "Render/RenderTexture.h"

namespace GE
{
	QuadActor::QuadActor()
	{
		std::shared_ptr<StaticMeshComponent> meshComponent = std::make_shared<StaticMeshComponent>();
		
		AddComponent(meshComponent);

		meshComponent->SetMesh(std::make_shared<QuardMesh>());
		std::weak_ptr<TextureMappingShader> shader;
		if (ShaderLoader::Get().Load<TextureMappingShader>(shader))
		{
			meshComponent->AddShader(shader);
		}

		// 텍스처 로드 및 셰이더에 설정
		std::weak_ptr<RenderTexture> renderTexture;
		TextureLoader::Get().GetNewRenderTexture(renderTexture, 1280, 800);

		shader.lock()->SetTexture(renderTexture);

		
	}
	void QuadActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		static const float rotationSpeed = 10.0f;
		// 회전
		//transform.rotation.y += deltaTime * rotationSpeed;
	}
}