#pragma once

#include "KeyCodes.h"

class Input
{
public:
	static bool GetKey(int keycode);
	static bool GetMouseButton(int button);
	static glm::vec2 GetMousePosition();
	static float GetMouseX();
	static float GetMouseY();
};