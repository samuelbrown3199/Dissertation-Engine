#include "TestUI.h"

void TestUI::InitializeUI()
{
	std::shared_ptr<Font> font = ResourceManager::LoadFont("Resources\\Fonts\\arial.ttf", 25);
	std::shared_ptr<UILabel> textTest = AddUIElement<UILabel>(1, glm::vec2(35.0f, 35.0f), 1.0f, "Sample Text, qpbd QPBD", glm::vec3(0.0, 0.0, 0.0), font);

	std::shared_ptr<UIBox> boxTest = AddUIElement<UIBox>(0, glm::vec2(25.0f, 25.0f), glm::vec2(350, 50), "Resources\\Textures\\test.png");
	//buttonTest = AddUIElement<UIButton>(0, glm::vec2(80.0f, 25.0f), glm::vec2(50, 50), "Resources\\Textures\\testspritesheet.png", "Resources\\Textures\\test.png", "Resources\\Textures\\test2.png");
	/*std::shared_ptr<UIToggle> toggleText = AddUIElement<UIToggle>(2, false, "Resources\\Textures\\test.png", "Resources\\Textures\\testspritesheet.png",
		glm::vec2(25.0f, 75.0f), glm::vec2(25, 25), 1.0f, "Toggle Test", glm::vec3(1.0, 1.0, 1.0), font);
		*/
	std::shared_ptr<UIWindow> windowTest = AddUIElement<UIWindow>(1, glm::vec2(0, 0), glm::vec2(250, 250), true, "Resources\\Textures\\testspritesheet.png");
	windowTest->AddUIElement<UIToggle>(2, false, "Resources\\Textures\\test.png", "Resources\\Textures\\testspritesheet.png",
		glm::vec2(25.0f, 75.0f), glm::vec2(25, 25), 1.0f, "Toggle Test", glm::vec3(1.0, 1.0, 1.0), font);
}

void TestUI::HandleEvents()
{
	/*if (buttonTest->ClickedOn())
	{
		std::cout << "Clicked!" << std::endl;
	}*/
}
