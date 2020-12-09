#include <iostream>

#include "System.h"
#include "MeshRenderer.h"

namespace NobleEngine
{
	struct MeshRendererSystem : public System<MeshRenderer>
	{
		void Render();
		void RenderMesh(std::shared_ptr<MeshRenderer> mesh);
	};
}