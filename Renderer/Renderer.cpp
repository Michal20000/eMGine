#include "Renderer.hpp"

void Renderer::m_DrawObject(MeshData& mesh_data)
{
	;

}

void Renderer::OnFrame(EntityEngine& ee, float delta_time)
{

	for (EntityView view = ee.View<MeshData>(); view.Verify(); ++view)
	{
		Entity entity = view.Record();
		MeshData mesh_data = view.Fragment<MeshData>();
		m_DrawObject(mesh_data);
	}

}