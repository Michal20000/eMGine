#pragma once
#include <cstdint>
#include <glm.hpp>
#include "EntityEngine.hpp"
#include "Mesh.hpp"
#include "Drawable.hpp"

namespace BasicShapes
{
	class CreateCubeEvent
	{
		public:
		static void OnEvent(EntityEngine& ee, CreateCubeEvent& event);
		
	};
	
}

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
