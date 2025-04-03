#include "CameraComponent.h"
#include "Core/Engine.h"
#include "Core/Common.h"
#include "Math/Matrix4.h"
#include "Actor/Actor.h"

namespace GE
{
	CameraComponent::CameraComponent()
	{
		// ����� ������Ʈ �� ���ε�.
		/*data.viewMatrix
			= Matrix4::Translation(owner->transform.position * -1.0f)
			* Matrix4::Transpose(Matrix4::Rotation(owner->transform.rotation));*/

		// ��� ��ġ.
		data.viewMatrix = Matrix4::Transpose(data.viewMatrix);

		// ������ ��Ƽ� ���� ����.
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(CameraBuffer);
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		// ���� ������.
		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &data;

		// ���� ����.
		ID3D11Device& device = Engine::Get().Device();
		ThrowIfFailed(
			device.CreateBuffer(&bufferDesc, &bufferData, &cameraBuffer),
			TEXT("Failed to create camera buffer."));
	}

	CameraComponent::~CameraComponent()
	{
	}

	void CameraComponent::Draw()
	{
		Component::Draw();

		// �� ��� ������Ʈ �� ���ε�
		data.viewMatrix =
			Matrix4::Translation(owner->transform.position * (-1.0f)) *
			Matrix4::Transpose(Matrix4::Rotation(owner->transform.rotation));


		//
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// ��ġ ��� (CPU�� GPU�� ����� �ٷ�� ����� �޶�).
		// ����� ����� �� ���� ��ķ� ��ȯ�ϱ� ���� ��ġ��� ó�� -> �̰� GPU�� �����ϴ� ���

		data.viewMatrix = Matrix4::Transpose(data.viewMatrix);

		// ���� ������Ʈ
		D3D11_MAPPED_SUBRESOURCE resource = {};

		// CPU�� ������ �ۼ��߿��� GPU���� ��������� ���� ����
		context.Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

		//resource.pData = &transformMatrix;
		// ����
		memcpy(resource.pData, &data, sizeof(CameraBuffer));
		// �� Ǯ��
		context.Unmap(cameraBuffer, 0);

		// ���� ���ε�
		// � ������ ����Ұ��� �˷��ִ°�
		context.VSSetConstantBuffers(1, 1, &cameraBuffer);
	}
}