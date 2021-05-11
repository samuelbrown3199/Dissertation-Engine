#include <NobleEngine/EngineCore.h>
#include <NobleEngine/EngineCore/System.h>

#include "Deleter.h"

using namespace NobleEngine;
struct DeleterSystem : public System<Deleter>
{
	void OnUpdate(std::shared_ptr<Deleter> comp);
};