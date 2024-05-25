#pragma once
#include "Dependencies/GL3W/include/gl3w.h"
#include "Dependencies/glm/glm.hpp"
#include "RendererUtilities.hpp"
#include "MeshData.hpp"
#include "EntityEngine/EntityEngine.hpp"

namespace BasicShapes
{
	class CreateCubeEvent
	{
		public:
		static void OnEvent(EntityEngine& ee, CreateCubeEvent& event)
		{
			//przepisz na pos vec3, normal vec3, color vec3
			glm::vec3 positions[]
			{
				{-0.5f, -0.5f, -0.5f},
				{0.5f, -0.5f, -0.5f},
				{0.5f, 0.5f, -0.5f},
				{-0.5f, 0.5f, -0.5f},
				{0.5f, -0.5f, 0.5f},
				{-0.5f, -0.5f, 0.5f},
				{-0.5f, 0.5f, 0.5f},
				{0.5f, 0.5f, 0.5f},
				{-0.5f, -0.5f, 0.5f},
				{0.5f, -0.5f, 0.5f},
				{0.5f, -0.5f, -0.5f},
				{-0.5f, -0.5f, -0.5f},
				{-0.5f, 0.5f, -0.5f},
				{0.5f, 0.5f, -0.5f},
				{0.5f, 0.5f, 0.5f},
				{-0.5f, 0.5f, 0.5f},
				{-0.5f, -0.5f, 0.5f},
				{-0.5f, -0.5f, -0.5f},
				{-0.5f, 0.5f, -0.5f},
				{-0.5f, 0.5f, 0.5f},
				{0.5f, -0.5f, -0.5f},
				{0.5f, -0.5f, 0.5f}, 
				{0.5f, 0.5f, 0.5f}, 
				{0.5f, 0.5f, -0.5f}, 
			};
			glm::vec3 normals[]
			{
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, 1.f},
				{0.f, 0.f, 1.f},
				{0.f, 0.f, 1.f},
				{0.f, 0.f, 1.f},
				{0.f, 1.f, 0.f},
				{0.f, 1.f, 0.f},
				{0.f, 1.f, 0.f},
				{0.f, 1.f, 0.f},
				{0.f, -1.f, 0.f},
				{0.f, -1.f, 0.f},
				{0.f, -1.f, 0.f},
				{0.f, -1.f, 0.f},
				{1.f, 0.f, 0.f},
				{1.f, 0.f, 0.f},
				{1.f, 0.f, 0.f},
				{1.f, 0.f, 0.f},
				{-1.f, 0.f, 0.f},
				{-1.f, 0.f, 0.f},
				{-1.f, 0.f, 0.f},
				{-1.f, 0.f, 0.f},
			};



			/*
			Vertex vertices[] //vec3 inPos, vec3 normal, vec3 color/uvw
			{
				{, {0.f, 0.f, 0.f}},	//0-8 bottom
				{, {1.f, 0.f, 0.f}},	//1-9 bottom
				{, {1.f, 1.f, 0.f}},	//2-10 bottom
				{ , {0.f, 1.f, 0.f}},	//3-11 bottom

				{ {1.f, 1.f, 0.f}},	//4-12 top
				{  {0.f, 1.f, 0.f}},	//5-13 top
				{ {0.f, 0.f, 0.f}},	//6-14 top
				{ {1.f, 0.f, 0.f}},		//7-15 top
				
				{ {0.f, 1.f, 0.f}}, 	// 13-5 front
				{ {1.f, 1.f, 0.f}}, 	// 12-4 front
				{ {1.f, 0.f, 0.f}}, 	// 9-1 front
				{ {0.f, 0.f, 0.f}}, 	// 8-0 front

				{, {0.f, 1.f, 0.f}}, // 11-3 back
				{, {1.f, 1.f, 0.f}}, // 10-2 back
				{, {1.f, 0.f, 0.f}}, // 15-7 back
				{, {0.f, 0.f, 0.f}}, // 14-6 back

				{ {0.f, 1.f, 0.f}}, // 21-5 left
				{ {0.f, 0.f, 0.f}}, // 16-0 left
				{ {0.f, 1.f, 0.f}}, // 19-3 left
				{ {0.f, 0.f, 0.f}}, // 22-6 left

				{, {1.f, 0.f, 0.f}}, // 17-1 right
				{, {1.f, 1.f, 0.f}}, // 20-4 right
				{, {1.f, 0.f, 0.f}}, // 23-7 right
				{, {1.f, 1.f, 0.f}}, // 18-2 right
			};
			*/

			Entity entity = ee.CreateEntity();
			ee.Attach<MeshData>(entity);
		}
	};
}