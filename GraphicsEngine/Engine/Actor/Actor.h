#pragma once

// 해시로 주는게 좋긴함
#include <string>
#include <vector>
#include <memory>

#include "Math/Transform.h" // 설계 시 고려할 상항

namespace GE
{
	class Actor
	{
		// Get Set이 맞긴한데 할게 많아서 그냥 사용함
		friend class Renderer;
		friend class Level;
		// 설계 시 고려사항
		// 얼마나 액터에 담을건지 - Unity는 아무것도 없음, Unreal은 좀 크게 봄
		// Unreal은 Actor를 기준으로 리플리케이션을 함
		// Unity는 Component를 기준으로 리플리케이션 함 
		// 이 기준은 네트워크 설계시 매우 중요하게 작용
	public:
		Actor();
		virtual ~Actor();

		virtual void BeginePlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void Destory();

		// 컴포넌트 추가함수
		void AddComponent(std::shared_ptr<class Component> newComponent);

		inline const bool IsActive() const { return isActive && !hasDestroyed; }
		inline const bool HasInitialized() const { return hasDestroyed; }


	public:
		// 엑터의 TRS 정보를 관리하는 트랜스폼
		Transform transform;

	protected:
		// 엑터의 이름 (일반적으로는 HASH로 변환해서 사용).
		std::wstring name = TEXT("Actor");
		// 액터의 초기화 여부
		bool hasInitialized = false;

		// 액터의 활성화 여부
		bool isActive = true;
		// 삭제 여부
		bool hasDestroyed = false;

		// 컴포넌트 배열
		std::vector < std::shared_ptr<class Component>> components;
	};
}
