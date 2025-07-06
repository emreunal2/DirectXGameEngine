#pragma once
#include <DX3D/Prerequisites.h>
#include <tuple>
#include <DX3D/Entity/Component.h>

struct CollisionPair {
	Component* a;
	Component* b;

	bool operator<(const CollisionPair& other) const {
		return std::tie(a, b) < std::tie(other.a, other.b);
	}
};

