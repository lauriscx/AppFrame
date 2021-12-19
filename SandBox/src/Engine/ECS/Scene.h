#pragma once
#include "Core/Core.h"
#include "entt.hpp"




class Entity;

class ENGINE_API Scene {
public:
	Scene();

	Entity createEntity();

	~Scene();
private:
	friend Entity;
	entt::registry m_Registry;
};

