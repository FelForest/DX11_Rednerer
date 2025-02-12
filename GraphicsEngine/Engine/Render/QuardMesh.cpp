#include "QuardMesh.h"
#include "../Shader/Shader.h"

namespace GE
{
	QuardMesh::QuardMesh()
	{
        // ���� �迭.
        std::vector<Vertex> vertices =
        {
            Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f)),
            Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f))
        };

        // �ε��� �迭.
        std::vector<uint32> indices = { 0, 1, 2, 3, 0 };

        meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
        shaders.emplace_back(std::make_shared<Shader>());
	}
}