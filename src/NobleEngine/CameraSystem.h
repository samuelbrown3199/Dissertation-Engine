#include "System.h"

#include "Camera.h"

namespace NobleEngine
{
	struct CameraSystem : public System<Camera>
	{
		void Update();
		void UpdateCameraView(std::shared_ptr<Camera> cam);
	};
}