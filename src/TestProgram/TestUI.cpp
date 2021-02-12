#include "TestUI.h"

void TestUI::InitializeUI()
{
	std::shared_ptr<UILabel> textTest = AddUIElement<UILabel>(glm::vec2(25.0f, 25.0f), glm::vec2(100, 50));
	textTest->labelFont = ResourceManager::LoadResource<Font>("Resources\\Fonts\\test.ttf");
	textTest->text = "This is sample text";

	std::shared_ptr<UIBox> boxTest = AddUIElement<UIBox>(glm::vec2(25.0f, 25.0f), glm::vec2(50, 50), "Resources\\Textures\\testspritesheet.png");
	buttonTest = AddUIElement<UIButton>(glm::vec2(80.0f, 25.0f), glm::vec2(50, 50), "Resources\\Textures\\testspritesheet.png", "Resources\\Textures\\test.png", "Resources\\Textures\\test2.png");
}

void TestUI::HandleEvents()
{
	if (buttonTest->ClickedOn())
	{
		std::cout << "Clicked!" << std::endl;
	}
}
