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

		// �����ؼ� �ߴ� ����ó���� ���⼭ �ϴ°� �´ٰ� �Ǵ� -> �ѹ��� Ÿ�� �� ������ �ֳ�? -> �׷��� �׷��� �ᱹ �������� ������� �ϴϱ� �ǹ��ֳ�?
		for (const auto& actor : actors)
		{
			actor->Tick(deltaTime);
		}
	}

	void Level::AddActor(std::shared_ptr<Actor> newActor)
	{
		// ���� �߰��ϴ� ���Ͱ� ī�޶� ������Ʈ�� �������� Ȯ��
		// �����ٸ� ���� ī�޶�� ����
		for (auto component : newActor->components)
		{
			std::shared_ptr<CameraComponent> cameraComponent = std::dynamic_pointer_cast<CameraComponent>(component);

			if (cameraComponent)
			{
				// ī�޶�� Ư�� ������ ���� actors�� �ȳ���
				cameraActor = newActor;
				return;
			}
		}

		// ������ �̹� �ִ� ���Ͱ� �ٽ� ���� ���� ���� ������� �ؾ���
		actors.emplace_back(newActor);
	}
	std::shared_ptr<Actor> Level::GetActor(int index) const
	{
		// ����ó��
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
