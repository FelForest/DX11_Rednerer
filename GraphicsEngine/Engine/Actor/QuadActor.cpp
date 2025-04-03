#include "QuadActor.h"

#include "Component/StaticMeshComponent.h"
#include "Render/QuardMesh.h"
#include "Shader/TextureMappingShader.h"
#include "Resource/ShaderLoader.h"

namespace GE
{
	QuadActor::QuadActor()
	{
		std::shared_ptr<StaticMeshComponent> meshComponent = std::make_shared<StaticMeshComponent>();
		
		AddComponent(meshComponent);

		meshComponent->SetMesh(std::make_shared<QuardMesh>());

		std::weak_ptr<TextureMappingShader> shader;
		if (ShaderLoader::Get().Load<TextureMappingShader>(shader, "T_coord.png"))
		{
			meshComponent->AddShader(shader);
		}
	}
}