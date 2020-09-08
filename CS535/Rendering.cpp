#include "Rendering.h"

glm::vec4 CS535::Convert(CS535::vec4 v)
{
	return glm::vec4(v.x, v.y, v.z, v.w);
}

glm::mat4 CS535::Convert(CS535::mat4 m)
{
	return glm::mat4(Convert(m.value[0]), Convert(m.value[1]), Convert(m.value[2]), Convert(m.value[3]));
}

void CS535::Graphics::DrawGizmoMesh(Mesh* mesh, CS535::vec4 color, RenderTarget* target, CS535::mat4 model, float size)
{
	glm::vec4 c = Convert(color);
	glm::mat4 m = Convert(model);
	RenderManager::DrawGizmoMesh(mesh, c, target, m, size);
}

void CS535::Graphics::DrawGizmoMeshInstanced(Mesh* mesh, CS535::vec4 color, CS535::mat4* matrices, size_t count, RenderTarget* target, CS535::mat4 model, float size)
{
	RenderManager::DrawGizmoMeshInstanced(mesh, Convert(color), (glm::mat4*)(void*)matrices, count, target, Convert(model), size);
}
