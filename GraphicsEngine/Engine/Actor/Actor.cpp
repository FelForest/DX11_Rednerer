#include "Actor.h"
#include "Component/Component.h"

namespace GE
{
	Actor::Actor()
	{
	}

	Actor::~Actor()
	{
	}

	void Actor::BeginePlay()
	{
		// 예외처리
		if (hasInitialized)
		{
			return;
		}
		// 초기화 설정
		hasInitialized = true;

		// 컴포넌트 함수 호출
		for (const auto& component : components)
		{
			component->BeginPlay();
		}
	}

	void Actor::Tick(float deltaTime)
	{
		// 예외처리 - 어디서 하든 상관 없음
		if (!IsActive())
		{
			return;
		}

		// 트랜스폼 업데이트
		transform.Tick();

		// 컴포넌트 함수 호출
		for (const auto& component : components)
		{
			component->Tick(deltaTime);
		}
	}

	void Actor::Draw()
	{
		// 예외처리
		if (!IsActive())
		{
			return;
		}

		// 트랜스폼 바인딩 ( 셰이더에 데이터 전달)
		transform.Bind();

		// 컴포넌트 함수 호출
		for (const auto& component : components)
		{
			component->Draw();
		}
	}

	void Actor::Destory()
	{
		hasDestroyed = true;
	}

	void Actor::AddComponent(std::shared_ptr<Component> newComponent)
	{
		// 컴포넌트 배열에 새로운 컴포넌트 추가
		components.emplace_back(newComponent);

		// 컴포넌트의 소유 설정
		newComponent->SetOwner(this);
	}
}