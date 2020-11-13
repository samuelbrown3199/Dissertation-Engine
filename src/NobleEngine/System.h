#include <memory>
#include <vector>
#include <string>

namespace NobleEngine
{
	struct System
	{
		std::vector<std::string> targetTags;

		virtual void Initialize() {};
		virtual void Update() {};
		virtual void Render() {};
	};
}