#include "System.h"

#include "Camera.h"

namespace NobleEngine
{
	struct CameraSystem : public System<Camera>
	{
		void OnUpdate(std::shared_ptr<Camera> comp);
		void UpdateCameraView(std::shared_ptr<Camera> cam);
	};
}