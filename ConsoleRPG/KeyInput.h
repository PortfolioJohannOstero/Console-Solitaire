#pragma once

#include <Windows.h>

class KeyInput
{
public:
	static bool KeyDown(int keycode);
	static bool KeyUp(int keycode);

private:
	static int keyPressed;
};
