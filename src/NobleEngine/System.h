#include <memory>
#include <vector>
#include <string>

namespace NobleEngine
{
	/**
	*System struct that component systems can inherit from. Systems handle game functionality.
	*/
	struct System
	{
		/**
		*Stores the tags that the system targets. Makes it possible to target specific entities with certain tags.
		*/
		std::vector<std::string> targetTags;

		/**
		*Setup for use in initializing components.
		*/
		virtual void Initialize() {};
		/**
		*Update is called every frame.
		*/
		virtual void Update() {};
		/**
		*Render is called every frame.
		*/
		virtual void Render() {};
	};
}