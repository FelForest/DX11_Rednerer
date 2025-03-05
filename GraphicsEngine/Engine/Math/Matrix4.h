#pragma once

#include "Core/Type.h"
#include "Vector3.h"

namespace GE
{
	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(const Matrix4& other);
		~Matrix4() = default;

		// �޸� �ʺ�(���� : ����Ʈ).
		static uint32 Stride() { return sizeof(Matrix4); }

		static Matrix4 Rotation(const Vector3& rotation);
		static Matrix4 Rotation(float);

		static Matrix4 RotationX(float angle);
		static Matrix4 RotationY(float angle);
		static Matrix4 RotationZ(float angle);

		// Degree <-> Radian
		// ������ const�� ���� �ϰ� �����δ� cpp���� �ؾ���
		static Matrix4 Identity;
		static constexpr float degreeToRadian = 3.141592f / 180.0f;
		static constexpr float radianToDegree = 180.0f / 3.141592f;
	private:
		// ����ü
		union
		{
			struct
			{
				// ���� ���ٿ�
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};

			// memset��
			float elements[4 * 4];
		};
	};
}
