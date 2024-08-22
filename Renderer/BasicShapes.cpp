#include "BasicShapes.hpp"

void BasicShapes::CreateCubeEvent::OnEvent(EntityEngine& ee, CreateCubeEvent& event)
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

	uint32_t indices[]
	{
		0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
		12, 13, 14, 15,
		16, 17, 18, 19,
		20, 21, 22, 23
	};

	Mesh mesh;
	mesh.LoadFromProgram(24, positions, normals, 24, indices);

	Entity entity = ee.CreateEntity();
	ee.Attach<Drawable>(entity);
	Drawable& drawable = ee.Fragment<Drawable>(entity);
	drawable.SetMesh(mesh);

}
