#include "Component.h"

#include "Model.h"

namespace NobleEngine
{
	struct MeshRenderer : public Component<MeshRenderer>
	{
		std::shared_ptr<Model> model;
	};
}