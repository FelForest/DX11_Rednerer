#pragma once
#include <string>
#include "../Core/Type.h"

namespace GE
{
	class Vector3
	{
	public:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		Vector3(float value);
		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

		static uint32 Stride()
		{
			return sizeof(Vector3);
		}

		// 연산자 오버로딩
		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);
		Vector3& operator*=(float scale);
		Vector3& operator/=(float scale);

		bool operator==(const Vector3& other);
		bool operator!=(const Vector3& other);

		Vector3 operator-() const;

		friend Vector3 operator+(const Vector3& left, const Vector3& right);
		friend Vector3 operator-(const Vector3& left, const Vector3& right);

		friend Vector3 operator*(const Vector3& vector, float scale);
		friend Vector3 operator*(float scale, const Vector3& vector);

		friend Vector3 operator/(const Vector3& vector, float scale);

		// (x, y) 문자열 생성 함수
		std::wstring ToString();

		// 길이 구하기
		float Length();
		float LengthSquared();



		// 내적
		friend float Dot(const Vector3& left, const Vector3& right);
		// 외적
		friend Vector3 Cross(const Vector3& left, const Vector3& right);

		Vector3 Normalized();
		bool Equals(const Vector3& other);

		// 선형 보간
		// (1-t)*from + t*to
		// t로 묶는것도 가능
		friend Vector3 Lerp(const Vector3& from, const Vector3& to, float t);
		// 기본 값
		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 Right;
		static const Vector3 Left;
		static const Vector3 Up;
		static const Vector3 Forward;
	};
}