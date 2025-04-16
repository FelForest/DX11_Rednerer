﻿#include "QuardMesh.h"
#include "../Shader/Shader.h"
#include "Shader/TextureMappingShader.h"
#include "Resource/ShaderLoader.h"
#include "Resource//ModelLoader.h"

#include "Math/Matrix4.h"
#include "Math/Vector3.h"

namespace GE
{
	QuardMesh::QuardMesh()
	{
        std::weak_ptr<MeshData> mesh;
        if (ModelLoader::Get().Load("quad.obj", mesh))
        {
            meshes.emplace_back(mesh);
        }
	}

    void QuardMesh::Update(float deltaTime)
    {
        // 회전 처리
        //static float angle = 0.0f;
        //angle += 60.0f * deltaTime;


        // 회전 적용
        //transform.rotation.z = angle;

        //Rotate(angle);
    }

    void QuardMesh::Rotate(float angle)
    {
        //// 정점 배열.
        //std::vector<Vertex> vertices =
        //{
        //    Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f)),
        //    Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)),
        //    Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f)),
        //    Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f))
        //};

        //static std::vector<Vertex> result;
        //static bool hasInitialized = false;

        //if (!hasInitialized)
        //{
        //    hasInitialized = true;
        //    result.assign(vertices.begin(), vertices.end());
        //}

        //// 회전 처리 
        //Matrix4 rotation = Matrix4::RotationZ(angle);
        //result[0].position = vertices[0].position * rotation;
        //result[1].position = vertices[1].position * rotation;
        //result[2].position = vertices[2].position * rotation;
        //result[3].position = vertices[3].position * rotation;

        //// 메시의 정점 버퍼 업데이트
        //meshes[0].lock()->UpdateVertexBuffer(result);

    }
}