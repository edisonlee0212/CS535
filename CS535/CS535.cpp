#include "UniEngine.h"
#include "CameraControlSystem.h"
#include "EntityEditorSystem.h"
#include "Rendering.h"
using namespace UniEngine;
void InitGround();
glm::vec4 ConvertVec4(CS535::vec4 v)
{
	return glm::vec4(v.x, v.y, v.z, v.w);
}
glm::mat4 ConvertMat4(CS535::mat4 m)
{
	return glm::mat4(ConvertVec4(m.value[0]), ConvertVec4(m.value[1]), ConvertVec4(m.value[2]), ConvertVec4(m.value[3]));
}

int main()
{
#pragma region Lighting and Shadow settings
	LightingManager::SetDirectionalLightResolution(2048);
	LightingManager::SetStableFit(true);
	LightingManager::SetSeamFixRatio(0.05f);
	LightingManager::SetMaxShadowDistance(200);
	LightingManager::SetVSMMaxVariance(0.001f);
	LightingManager::SetEVSMExponent(80.0f);
	LightingManager::SetSplitRatio(0.15f, 0.3f, 0.5f, 1.0f);
#pragma endregion
	FileIO::SetResourcePath("../UniEngine/Resources/");
	Application::Init();
#pragma region Lights
	EntityArchetype lightArchetype = EntityManager::CreateEntityArchetype("Light", Translation(), Rotation(), LocalToWorld());
	DirectionalLightComponent* dlc = new DirectionalLightComponent();
	dlc->diffuse = glm::vec3(0.7f);
	dlc->specular = glm::vec3(0.3f);
	Entity dle = EntityManager::CreateEntity(lightArchetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle, dlc);
	DirectionalLightComponent* dlc2 = new DirectionalLightComponent();
	Entity dle2 = EntityManager::CreateEntity(lightArchetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle2, dlc2);
	Rotation r;
	r.Value = glm::quatLookAt(
		glm::normalize(glm::vec3(
			glm::cos(glm::radians(80.0f)) * glm::sin(0),
			glm::sin(glm::radians(80.0f)),
			glm::cos(glm::radians(80.0f)) * glm::cos(0)))
		, glm::vec3(0, 1, 0));
	EntityManager::SetComponentData<Rotation>(dle, r);
#pragma endregion
#pragma region Preparations
	World* world = Application::GetWorld();
	WorldTime* time = world->Time();
	EntityEditorSystem* editorSystem = world->CreateSystem<EntityEditorSystem>(SystemGroup::PresentationSystemGroup);
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(20.0f);
	ccs->Enable();
	ccs->EnableWindowControl(false);
	ccs->SetPosition(glm::vec3(0, 20, 60));
#pragma endregion
	EntityArchetype pointArchetype = EntityManager::CreateEntityArchetype("Point", LocalToWorld());
	EntityArchetype axisArchetype = EntityManager::CreateEntityArchetype("Axis", Translation(), Scale(), Rotation(), LocalToWorld());
	MeshMaterialComponent* pmmc = new MeshMaterialComponent();
	pmmc->_Mesh = Default::Primitives::Sphere;
	pmmc->_Material = Default::Materials::StandardMaterial;
	MeshMaterialComponent* ammc = new MeshMaterialComponent();
	ammc->_Mesh = Default::Primitives::Cylinder;
	ammc->_Material = Default::Materials::StandardMaterial;
	Scale scale;
	scale.Value = glm::vec3(1.0f);

	Entity point = EntityManager::CreateEntity(pointArchetype);
	EntityManager::SetSharedComponent(point, pmmc);

	Translation t;
	t.Value = glm::vec3(0, 0, 10);
	r.Value = glm::quat(glm::vec3(glm::radians(-45.0f), 0.0f, 0.0f));
	scale.Value = glm::vec3(0.2f, 30.0f, 0.2f);
	Entity axis = EntityManager::CreateEntity(axisArchetype);
	EntityManager::SetSharedComponent(axis, ammc);
	EntityManager::SetComponentData(axis, scale);
	EntityManager::SetComponentData(axis, t);
	EntityManager::SetComponentData(axis, r);

	LocalToWorld ltw;
	CS535::vec3 position(0, 0, 0);
	auto pointMatrix = CS535::Translate(CS535::mat4::Identity(), position);
	InitGround();
	bool loopable = true;
	//Start engine. Here since we need to inject procedures to the main engine loop we need to manually loop by our self.
	while (loopable) {
		Application::PreUpdate();
		float time = Application::GetWorld()->Time()->Time();
		position = CS535::RotateAround(CS535::vec3(0, 20, 0), CS535::vec3(0, 0, 10), CS535::vec3(0, 10, -10), CS535::Radians(time * 30.0f));
		pointMatrix = CS535::Translate(CS535::mat4::Identity(), position) * CS535::Scale(CS535::mat4::Identity(), CS535::vec3(1.0, 1.0, 1.0));
		
		Application::Update();
		ltw.Value = ConvertMat4(pointMatrix);
		EntityManager::SetComponentData(point, ltw);
		loopable = Application::LateUpdate();
	}
	Application::End();
	return 0;
}

void InitGround() {
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("Ground", Translation(), Scale(), LocalToWorld());
	auto entity = EntityManager::CreateEntity(archetype);
	Translation translation = Translation();
	translation.Value = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale scale = Scale();
	scale.Value = glm::vec3(50.0f);
	EntityManager::SetComponentData<Translation>(entity, translation);
	EntityManager::SetComponentData<Scale>(entity, scale);


	auto mat = new Material();
	mat->Programs()->push_back(Default::GLPrograms::StandardProgram);
	auto texture = new Texture2D(TextureType::DIFFUSE);
	texture->LoadTexture(FileIO::GetResourcePath("Textures/white.png"), "");
	mat->Textures2Ds()->push_back(texture);
	mat->SetMaterialProperty("material.shininess", 32.0f);
	MeshMaterialComponent* meshMaterial = new MeshMaterialComponent();
	meshMaterial->_Mesh = Default::Primitives::Quad;
	meshMaterial->_Material = mat;
	EntityManager::SetSharedComponent<MeshMaterialComponent>(entity, meshMaterial);

}