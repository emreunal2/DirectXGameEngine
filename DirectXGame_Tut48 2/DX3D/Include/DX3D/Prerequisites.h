

#pragma once
#include <memory>
#include <iostream>
#include <stdexcept>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class Texture2D;
class Font2D;
class RenderSystem;
class GraphicsEngine;
class Resource;
class ResourceManager;
class Texture;
class TextureManager;
class Mesh;
class MeshManager;
class Material;
class Font;
class FrameBuffer;
class Window;
class Game;
class Display;
class InputSystem;
class PhysicsEngine;


class Component;
class TransformComponent;
class MeshComponent;
class CameraComponent;
class LightComponent;
class TerrainComponent;
class WaterComponent;
class FogComponent;
class TextComponent;
class ImageComponent;
class PlayerControllerComponent;
class SphereColliderComponent;

class Entity;
class World;

using SwapChainPtr = std::shared_ptr<SwapChain>;
using DeviceContextPtr = std::shared_ptr<DeviceContext>;
using VertexBufferPtr = std::shared_ptr<VertexBuffer>;
using IndexBufferPtr = std::shared_ptr<IndexBuffer>;
using ConstantBufferPtr = std::shared_ptr<ConstantBuffer>;
using VertexShaderPtr = std::shared_ptr<VertexShader>;
using PixelShaderPtr = std::shared_ptr<PixelShader>;
using Texture2DPtr = std::shared_ptr<Texture2D>;
using Font2DPtr = std::shared_ptr<Font2D>;
using ResourcePtr = std::shared_ptr<Resource>;
using TexturePtr = std::shared_ptr<Texture>;
using MeshPtr = std::shared_ptr<Mesh>;
using MaterialPtr = std::shared_ptr<Material>;
using FontPtr = std::shared_ptr<Font>;
using FrameBufferPtr = std::shared_ptr<FrameBuffer>;

using ui32 = unsigned int;
using i32 = int;
using f32 = float;
using d64 = double;





enum class Key
{
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	Escape,
	Shift,
	Space,
	Enter,
	LeftMouseButton,
	MiddleMouseButton,
	RightMouseButton,
	ArrowUp,
	ArrowDown,
	ArrowLeft,
	ArrowRight,
	GreaterThan,
	LessThan,
	Minus,
	Equals
};

enum class CameraType
{
	Orthogonal =0,
	Perspective
};

enum class CullMode
{
	None = 0,
	Front,
	Back
};


#define DX3DError(message)\
{\
std::wclog << "DX3D Error: " << message << std::endl;\
throw std::runtime_error("");\
}

#define DX3DWarning(message)\
std::wclog << "DX3D Warning: " << message << std::endl;

#define DX3DInfo(message)\
std::wclog << "DX3D Info: " << message << std::endl;