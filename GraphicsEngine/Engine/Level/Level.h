#pragma once


#include <vector>
#include <memory>
#include "Core/Type.h"

namespace GE
{
	// 월드에 백치된 액터를 관리
	class Actor;
	class Level
	{
	public:
		Level();
		virtual ~Level();

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		void AddActor(std::shared_ptr<Actor> newActor);

		// Getter
		std::shared_ptr<Actor> GetActor(int index) const;
		const uint32 ActorCount() const;

		std::shared_ptr<Actor> GetCamera() const;

	protected:
		std::vector<std::shared_ptr<Actor>> actors;

		// 메인 카메라 액터
		std::shared_ptr<Actor> cameraActor;

	};


}