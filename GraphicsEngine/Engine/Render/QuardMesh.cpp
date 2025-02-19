#include "QuardMesh.h"
#include "../Shader/Shader.h"
#include "Shader/TextureMappingShader.h"

namespace GE
{
	QuardMesh::QuardMesh()
	{
        // 정점 배열.
        std::vector<Vertex> vertices =
        {
            Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f)),
            Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f))
        };

        // 인덱스 배열.
        std::vector<uint32> indices = { 1, 2, 3, 3, 0, 1 };

        meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
        shaders.emplace_back(std::make_shared<TextureMappingShader>("SuperMario.png"));
	}
}