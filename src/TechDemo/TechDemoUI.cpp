#include "TechDemoUI.h"

void TechDemoUI::InitializeUI()
{
	std::shared_ptr<Font> font = ResourceManager::LoadFont("Resources\\Fonts\\arial.ttf", 25);
	AddUIElement<UIBox>(0, glm::vec2(0, 0), glm::vec2(150, 350), "Resources\\Textures\\ui1.png");
}