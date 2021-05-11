#include <NobleEngine/EngineCore/Component.h>

using namespace NobleEngine;
struct Deleter : public Component<Deleter>
{
	int framesToDelete = 7000;
	int framesSinceCreation = 0;
};