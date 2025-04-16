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
		// 데모 씬(레벨) 구성
		std::shared_ptr<QuadActor> actor1 = std::make_shared<QuadActor>();
		actor1->transform.position = Vector3(0.0f, 0, 0);
		actor1->transform.rotation = Vector3(0, 150.0f, 180.0f);


		// 카메라 액터 생성
		std::shared_ptr<Actor> cameraActor = std::make_shared<Actor>();
		cameraActor->AddComponent(std::make_shared<CameraComponent>());
		// 엑터를 레벨에 추가
		AddActor(actor1);
		AddActor(cameraActor);

	}
	DemoLevel::~DemoLevel()
	{
	}
}