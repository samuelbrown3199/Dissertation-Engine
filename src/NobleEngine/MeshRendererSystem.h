#include <iostream>

#include "System.h"
#include "MeshRenderer.h"

namespace NobleEngine
{
	struct MeshRendererSystem : public System<MeshRenderer>
	{
		void OnRender(std::shared_ptr<MeshRenderer> comp);
		void RenderMesh(std::shared_ptr<MeshRenderer> mesh);
	};
}