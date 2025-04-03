#pragma once

// �ؽ÷� �ִ°� ������
#include <string>
#include <vector>
#include <memory>

#include "Math/Transform.h" // ���� �� ����� ����

namespace GE
{
	class Actor
	{
		// Get Set�� �±��ѵ� �Ұ� ���Ƽ� �׳� �����
		friend class Renderer;
		friend class Level;
		// ���� �� �������
		// �󸶳� ���Ϳ� �������� - Unity�� �ƹ��͵� ����, Unreal�� �� ũ�� ��
		// Unreal�� Actor�� �������� ���ø����̼��� ��
		// Unity�� Component�� �������� ���ø����̼� �� 
		// �� ������ ��Ʈ��ũ ����� �ſ� �߿��ϰ� �ۿ�
	public:
		Actor();
		virtual ~Actor();

		virtual void BeginePlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void Destory();

		// ������Ʈ �߰��Լ�
		void AddComponent(std::shared_ptr<class Component> newComponent);

		inline const bool IsActive() const { return isActive && !hasDestroyed; }
		inline const bool HasInitialized() const { return hasDestroyed; }


	public:
		// ������ TRS ������ �����ϴ� Ʈ������
		Transform transform;

	protected:
		// ������ �̸� (�Ϲ������δ� HASH�� ��ȯ�ؼ� ���).
		std::wstring name = TEXT("Actor");
		// ������ �ʱ�ȭ ����
		bool hasInitialized = false;

		// ������ Ȱ��ȭ ����
		bool isActive = true;
		// ���� ����
		bool hasDestroyed = false;

		// ������Ʈ �迭
		std::vector < std::shared_ptr<class Component>> components;
	};
}
