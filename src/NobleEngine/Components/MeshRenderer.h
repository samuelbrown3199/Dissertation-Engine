#include "../EngineCore/Component.h"

#include<string>

#include "../EngineCore/Application.h"
#include "../ResourceManagement/Model.h"
#include "../ResourceManagement/Material.h"
#include "../ResourceManagement/ShaderProgram.h"
#include "../EngineCore/ResourceManager.h"

namespace NobleEngine
{
	struct Transform;
	/**
	*Stores information to render a mesh. Takes a model, material, shader and a transform. Automatically bound to the engine on startup.
	*/
	struct MeshRenderer : public Component<MeshRenderer>
	{
		/**
		*The model that the mesh will render.
		*/
		std::shared_ptr<Model> model;
		/**
		*Material information for rendering.
		*/
		std::shared_ptr<Material> material;
		/**
		*The shader that will be used to render the mesh.
		*/
		std::shared_ptr<ShaderProgram> shader;
		/**
		*The meshes transform. Automatically found in the mesh renderer system.
		*/
		std::shared_ptr<Transform> transform;

		/**
		*Initializes the mesh renderer with a model and a material. Shader will default to the standard shader.
		*/
		void OnInitialize(std::string _modelDir, std::shared_ptr<Material> _mat)
		{
			model = ResourceManager::LoadResource<Model>(_modelDir);
			material = _mat;
			shader = Application::standardShader;
		}
		/**
		*Initializes the mesh renderer with a model, material and a shader.
		*/
		void OnInitialize(std::string _modelDir, std::shared_ptr<Material> _mat, std::shared_ptr<ShaderProgram> _sha)
		{
			model = ResourceManager::LoadResource<Model>(_modelDir);
			material = _mat;
			shader = _sha;
		}
	};
}