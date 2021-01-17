#include <iostream>

#include "System.h"
#include "MeshRenderer.h"

namespace NobleEngine
{
	/**
	*Handles the rendering of mesh renderers. Automatically bound to the engine on startup.
	*/
	struct MeshRendererSystem : public System<MeshRenderer>
	{
		void OnRender(std::shared_ptr<MeshRenderer> comp);
		void RenderMesh(std::shared_ptr<MeshRenderer> mesh);
	};
}