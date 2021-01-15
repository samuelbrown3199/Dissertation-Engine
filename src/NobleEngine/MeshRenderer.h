#include "Component.h"

#include<string>

#include "Model.h"
#include "Material.h"
#include "ShaderProgram.h"

namespace NobleEngine
{
	struct Transform;

	struct MeshRenderer : public Component<MeshRenderer>
	{
		std::shared_ptr<Model> model;
		std::shared_ptr<Material> material;
		std::shared_ptr<ShaderProgram> shader;
		std::shared_ptr<Transform> transform;
	};
}