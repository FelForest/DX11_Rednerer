﻿#pragma once

// 현재 경로 부터 찾음
#include "Math/Vector3.h"
#include "Math/Vector2.h"
namespace GE
{
    class Vertex
    {
    public:
        Vertex(
            const Vector3& position, 
            const Vector3& color, 
            const Vector2& texCoord,
            const Vector3& normal
        )
            : position(position), color(color), texCoord(texCoord), normal(normal)
        {
        }

        static unsigned int Stride() { return sizeof(Vertex); }

    public:
        // 정점의 위치
        Vector3 position;

        // 정점의 색상
        Vector3 color;

        // 정점 기준 텍스처 좌표
        Vector2 texCoord;

        // 노멀 (법선, Normal) 벡터
        Vector3 normal;

        // 폴리곤은 3점의 평균으로 만드는 건가?
    };
}