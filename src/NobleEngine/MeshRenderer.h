#include "Component.h"

#include "Model.h"
#include "Material.h"
#include "ShaderProgram.h"

namespace NobleEngine
{
	struct MeshRenderer : public Component<MeshRenderer>
	{
		std::shared_ptr<Model> model;
		std::shared_ptr<Material> material;
		std::shared_ptr<ShaderProgram> shader;
	};
}