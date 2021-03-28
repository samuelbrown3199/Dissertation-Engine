#include "../EngineCore/System.h"
#include "../Components/Camera.h"

namespace NobleEngine
{
	/**
	*Handles the generation of view matrices for the cameras in the engine. Automatically bound to the engine on startup.
	*/
	struct CameraSystem : public System<Camera>
	{
		/**
		*Updates the camera view matrix.
		*/
		void OnUpdate(std::shared_ptr<Camera> _comp);
	};
}