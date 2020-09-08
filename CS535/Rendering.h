#pragma once
#include "Math.h"
#include "UniEngine.h"
using namespace UniEngine;
namespace CS535 {
	static glm::vec4 Convert(CS535::vec4 v);
	static glm::mat4 Convert(CS535::mat4 m);
	class Graphics {
	public:
		static void DrawGizmoMesh(Mesh* mesh, CS535::vec4 color, RenderTarget* target, CS535::mat4 model = CS535::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoMeshInstanced(Mesh* mesh, CS535::vec4 color, CS535::mat4* matrices, size_t count, RenderTarget* target, CS535::mat4 model = CS535::mat4(1.0f), float size = 1.0f);
	};
}