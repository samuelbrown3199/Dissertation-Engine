#pragma once
#ifndef AUDIOLISTENER_H_
#define AUDIOLISTENER_H_

#include "Component.h"
#include "Transform.h"
#include "Entity.h"

namespace NobleEngine
{
	struct AudioListener : public Component<AudioListener>
	{
		std::shared_ptr<Transform> listenerTransform;

		void OnInitialize()
		{
			listenerTransform = GetEntity()->GetComponent<Transform>();
			if (!listenerTransform)
			{
				std::cout << "Entity " << entityID << " not valid audio listener due to no transform component attached!" << std::endl;
			}
		}
	};
}

#endif