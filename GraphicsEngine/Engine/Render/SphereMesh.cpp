#include "SphereMesh.h"
#include "../Shader/Shader.h"
#include "Shader/TextureMappingShader.h"
#include "Resource/ShaderLoader.h"
#include "Resource//ModelLoader.h"

#include "Math/Matrix4.h"
#include "Math/Vector3.h"

namespace GE
{
	SphereMesh::SphereMesh()
	{
		std::weak_ptr<MeshData> mesh;
		if (ModelLoader::Get().Load("sphere.obj", mesh))
		{
			meshes.emplace_back(mesh);
		}
	}
}