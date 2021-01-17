#include "Component.h"

#include<string>

#include "Application.h"
#include "Model.h"
#include "Material.h"
#include "ShaderProgram.h"
#include "ResourceManager.h"

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
		void OnInitialize(std::string modelDir, std::shared_ptr<Material> mat)
		{
			model = ResourceManager::LoadResource<Model>(modelDir);
			material = mat;
			shader = Application::standardShader;
		}
		/**
		*Initializes the mesh renderer with a model, material and a shader.
		*/
		void OnInitialize(std::string modelDir, std::shared_ptr<Material> mat, std::shared_ptr<ShaderProgram> sha)
		{
			model = ResourceManager::LoadResource<Model>(modelDir);
			material = mat;
			shader = sha;
		}
	};
}