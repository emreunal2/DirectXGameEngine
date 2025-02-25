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



#include <DX3D/Entity/Entity.h>
#include <DX3D/Entity/Component.h>
#include <DX3D/Entity/TransformComponent.h>
#include <DX3D/Entity/MeshComponent.h>
#include <DX3D/Entity/CameraComponent.h>
#include <DX3D/Entity/LightComponent.h>
#include <DX3D/Entity/TerrainComponent.h>
#include <DX3D/Entity/WaterComponent.h>
#include <DX3D/Entity/FogComponent.h>
#include <DX3D/Entity/TextComponent.h>
#include <DX3D/Entity/ImageComponent.h>
#include <DX3D/Entity/PlayerControllerComponent.h>
#include <DX3D/Entity/SphereColliderComponent.h>

#include <DX3D/Resource/ResourceManager.h>
#include <DX3D/Resource/Mesh.h>
#include <DX3D/Resource/Texture.h>
#include <DX3D/Resource/Material.h>
#include <DX3D/Resource/Font.h>

#include <DX3D/Input/InputSystem.h>

#include <DX3D/Game/Display.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>