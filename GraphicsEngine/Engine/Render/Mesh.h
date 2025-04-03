#pragma once

#include <vector>
#include <d3d11.h>
#include <memory>

#include "Vertex.h"
#include "../Core/Type.h"
#include "Math/Transform.h"

namespace GE
{
    // 메쉬 데이터 구조체.
    struct MeshData
    {
        MeshData();
        MeshData(
            const std::vector<Vertex>& vertices,
            const std::vector<uint32>& indices
        );
        ~MeshData();

        void Bind();
        uint32 IndexCount() const { return (uint32)indices.size(); }

        // 정점 데이터를 업데이트 하는 함수
        void UpdateVertexBuffer(const std::vector<Vertex>& vertices);

        // 정점 데이터.
        std::vector<Vertex> vertices;
        uint32 stride = 0;
        ID3D11Buffer* vertexBuffer = nullptr;

        // 인덱스 데이터.
        std::vector<uint32> indices;
        ID3D11Buffer* indexBuffer = nullptr;
    };

    class Mesh
    {
    public:
        Mesh();
        virtual ~Mesh() = default;

        // 컴포넌트 생겨서 필요 없어짐.
        //virtual void Draw();

    public:
        // 객체지향 생각하면 Get Set 만드는게 맞는데 지울건데 그때 합시다
        // @Temp: 트랜스폼 정보(임시) : 엑터 만들어지면 넘어갈 값
        //Transform transform;

        // 서브 메시 개수 변환 Getter
        uint32 SubMeshCount() const;

        std::weak_ptr<MeshData> GetSubMesh(int index) const;

    protected:
        //std::vector<std::shared_ptr<MeshData>> meshes;
        // 서브 메시
        std::vector<std::weak_ptr<MeshData>> meshes;
        //std::vector<std::shared_ptr<class Shader>> shaders;
        //std::vector<std::weak_ptr<class Shader>> shaders;



    };
}