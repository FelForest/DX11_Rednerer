#include "Level.h"
#include "Actor/Actor.h"
#include "Component/CameraComponent.h"
namespace GE
{
	Level::Level()
	{
	}

	Level::~Level()
	{
	}

	void Level::BeginPlay()
	{
		for (const auto& actor : actors)
		{
			actor->BeginePlay();
		}
	}

	void Level::Tick(float deltaTime)
	{
		if (cameraActor)
		{
			cameraActor->Tick(deltaTime);
		}

		// 액터해서 했던 예외처리를 여기서 하는게 맞다고 판단 -> 한번더 타고 들어갈 이유가 있나? -> 그런데 그러면 결국 액터한테 물어봐야 하니까 의미있나?
		for (const auto& actor : actors)
		{
			actor->Tick(deltaTime);
		}
	}

	void Level::AddActor(std::shared_ptr<Actor> newActor)
	{
		// 새로 추가하는 액터가 카메라 컴포넌트를 가졌는지 확인
		// 가졌다면 메인 카메라로 설정
		for (auto component : newActor->components)
		{
			std::shared_ptr<CameraComponent> cameraComponent = std::dynamic_pointer_cast<CameraComponent>(component);

			if (cameraComponent)
			{
				// 카메라는 특별 관리를 위해 actors에 안넣음
				cameraActor = newActor;
				return;
			}
		}

		// 원래는 이미 있는 액터가 다시 들어가는 것을 막는 방식으로 해야함
		actors.emplace_back(newActor);
	}
	std::shared_ptr<Actor> Level::GetActor(int index) const
	{
		// 예외처리
		if (index < 0 || index >= (int)actors.size())
		{
			return nullptr;
		}

		return actors[index];
	}
	const uint32 Level::ActorCount() const
	{
		return (uint32)actors.size();
	}
	std::shared_ptr<Actor> Level::GetCamera() const
	{
		return cameraActor;
	}
}
