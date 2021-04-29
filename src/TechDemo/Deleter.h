#include <NobleEngine/EngineCore/Component.h>

using namespace NobleEngine;
struct Deleter : public Component<Deleter>
{
	int framesToDelete = 1000;
	int framesSinceCreation = 0;
};