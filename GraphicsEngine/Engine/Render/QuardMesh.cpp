#include "QuardMesh.h"
#include "../Shader/Shader.h"
#include "Shader/TextureMappingShader.h"
#include "Resource/ShaderLoader.h"

namespace GE
{
	QuardMesh::QuardMesh()
	{
        // ���� �迭.
        std::vector<Vertex> vertices =
        {
            Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f)),
            Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(1.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f))
        };

        // �ε��� �迭.
        std::vector<uint32> indices = { 1, 2, 3, 3, 0, 1 };

        meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
        //shaders.emplace_back(std::make_shared<TextureMappingShader>("SuperMario.png"));
        std::weak_ptr<TextureMappingShader> shader;
        if (ShaderLoader::Get().Load<TextureMappingShader>(shader, "T_coord.png"))
        {
            shaders.emplace_back(shader);
        }
	}
}