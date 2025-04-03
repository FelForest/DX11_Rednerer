#include "DemoLevel.h"

#include "Actor/Actor.h"

#include "Resource/ShaderLoader.h"
#include "Resource/ModelLoader.h"
#include "Resource/TextureLoader.h"
#include "Shader/TextureMappingShader.h"

#include "Math/Transform.h"
#include "Math/Vector3.h"
#include "Actor/QuadActor.h"
#include "Component/CameraComponent.h"

namespace GE
{
	DemoLevel::DemoLevel()
	{
		// ���� ��(����) ����
		std::shared_ptr<QuadActor> actor = std::make_shared<QuadActor>();
		

		// ī�޶� ���� ����
		std::shared_ptr<Actor> cameraActor = std::make_shared<Actor>();
		cameraActor->AddComponent(std::make_shared<CameraComponent>());
		// ���͸� ������ �߰�
		AddActor(actor);
		AddActor(cameraActor);

	}
	DemoLevel::~DemoLevel()
	{
	}
}