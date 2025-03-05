#pragma once
#include "Mesh.h"

namespace GE
{
	class QuardMesh : public Mesh
	{
	public:
		QuardMesh();

		void Update(float deltaTime);

	private:
		void Rotate(float angle);
	};
}