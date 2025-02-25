/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2023, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Math/Vector2D.h>
#include <DX3D/Math/Rect.h>

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
public:
	bool isKeyDown(const Key& key);
	bool isKeyUp(const Key& key);
	Vector2D getDeltaMousePosition();

	void lockCursor(bool lock);
	void setLockArea(const Rect& area);


	void update();
private:
	short getInternalKeyCode(const Key& key);
private:	
	short m_keys_state[256] = {};
	short m_old_keys_state[256] = {};
	short m_final_keys_state[256] = {};

	bool m_cursorLocked = false;
	Rect m_lockArea;
	Vector2D m_lockAreaCenter;

	Vector2D m_deltaMousePos;
	Vector2D m_old_mouse_pos;
};

