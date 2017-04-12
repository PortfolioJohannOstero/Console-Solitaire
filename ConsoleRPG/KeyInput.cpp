#include "KeyInput.h"

int KeyInput::keyPressed = 0;

bool KeyInput::KeyDown(int keycode)
{
	return GetAsyncKeyState(keycode);
}

bool KeyInput::KeyUp(int keycode)
{
	if (!GetAsyncKeyState(keycode) && keycode == KeyInput::keyPressed)
	{
		keyPressed = 0;
		return true;
	}

	if(GetAsyncKeyState(keycode))
		keyPressed = keycode;
	
	return false;
}