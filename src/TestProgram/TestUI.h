#pragma once
#ifndef TESTUI_H_
#define TESTUI_H_

#include <NobleEngine/EngineCore.h>

using namespace NobleEngine;
struct TestUI : public UISystem
{
	std::shared_ptr<UIButton> buttonTest;

	void InitializeUI();
	void HandleEvents();
};

#endif