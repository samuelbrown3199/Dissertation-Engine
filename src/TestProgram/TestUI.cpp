#include "TestUI.h"

void TestUI::InitializeUI()
{
	std::shared_ptr<UIBox> boxTest = AddUIElement<UIBox>(glm::vec2(25.0f, 25.0f), glm::vec2(50, 50), "Resources\\Textures\\testspritesheet.png");
	buttonTest = AddUIElement<UIButton>(glm::vec2(80.0f, 25.0f), glm::vec2(50, 50), "Resources\\Textures\\testspritesheet.png", "Resources\\Textures\\test.png", "Resources\\Textures\\test2.png");

	std::shared_ptr<UILabel> textTest = AddUIElement<UILabel>(glm::vec2(25.0f, 50.0f), glm::vec2(100, 50));
	textTest->scale = 1.0f;
	textTest->labelFont = ResourceManager::LoadResource<Font>("Resources\\Fonts\\OptimusPrinceps.ttf");
	textTest->text = "This is sample text";
}

void TestUI::HandleEvents()
{
	if (buttonTest->ClickedOn())
	{
		std::cout << "Clicked!" << std::endl;
	}
}
