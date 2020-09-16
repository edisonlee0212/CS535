#include "UniEngine.h"
#include "CameraControlSystem.h"
#include "EntityEditorSystem.h"
#include "Rendering.h"
using namespace UniEngine;
void LightSettingMenu();
float lightAngle0 = 60;
float lightAngle1 = 0;
float lightDiffuse = 1.0f;
float lightSpecular = 0.2f;
float lightSize = 1.2f;
float pcssScale = 1.0f;

void InitGround();
void EngineSetup();

Entity ConstructEntityFromBin(EntityArchetype entityArchetype, std::string path);
glm::vec4 ConvertVec4(CS535::vec4 v)
{
	return glm::vec4(v.x, v.y, v.z, v.w);
}
glm::mat4 ConvertMat4(CS535::mat4 m)
{
	return glm::mat4(ConvertVec4(m.value[0]), ConvertVec4(m.value[1]), ConvertVec4(m.value[2]), ConvertVec4(m.value[3]));
}
#define ASSIGNMENT_2
int main()
{
	EngineSetup();
#pragma region Lights
	EntityArchetype lightArchetype = EntityManager::CreateEntityArchetype("Light", Translation(), Rotation(), LocalToWorld());
	DirectionalLightComponent* dlc = new DirectionalLightComponent();
	dlc->diffuse = glm::vec3(0.7f);
	dlc->specular = glm::vec3(0.3f);
	Entity dle = EntityManager::CreateEntity(lightArchetype);
	EntityManager::SetSharedComponent<DirectionalLightComponent>(dle, dlc);
	DirectionalLightComponent* dlc2 = new DirectionalLightComponent();
	Rotation r;
	r.Value = glm::quatLookAt(
		glm::normalize(glm::vec3(
			glm::cos(glm::radians(80.0f)) * glm::sin(0),
			glm::sin(glm::radians(80.0f)),
			glm::cos(glm::radians(80.0f)) * glm::cos(0)))
		, glm::vec3(0, 1, 0));
	EntityManager::SetComponentData<Rotation>(dle, r);
#pragma endregion
	
#ifdef ASSIGNMENT_1
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
	Rotation r;
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
#endif

#ifdef ASSIGNMENT_2
	Translation t;
	Scale s;
	
	EntityArchetype modelArchetype = EntityManager::CreateEntityArchetype("Model", Translation(), Scale(), Rotation(), LocalToWorld());
	Entity bunny = ConstructEntityFromBin(modelArchetype, "geometry/bunny.bin");
	t.Value = glm::vec3(-20.0f, 5.0f, 20.0f);
	s.Value = glm::vec3(50.0f);
	EntityManager::SetComponentData(bunny, t);
	EntityManager::SetComponentData(bunny, s);
	
	Entity DNA = ConstructEntityFromBin(modelArchetype, "geometry/DNA.bin");
	t.Value = glm::vec3(-20.0f, 5.0f, 0.0f);
	s.Value = glm::vec3(10.0f);
	EntityManager::SetComponentData(DNA, t);
	EntityManager::SetComponentData(DNA, s);

	Entity happy2 = ConstructEntityFromBin(modelArchetype, "geometry/happy2.bin");
	t.Value = glm::vec3(20.0f, 5.0f, 0.0f);
	s.Value = glm::vec3(30.0f);
	EntityManager::SetComponentData(happy2, t);
	EntityManager::SetComponentData(happy2, s);

	Entity happy4 = ConstructEntityFromBin(modelArchetype, "geometry/happy4.bin");
	t.Value = glm::vec3(0.0f, 5.0f, 0.0f);
	s.Value = glm::vec3(30.0f);
	EntityManager::SetComponentData(happy4, t);
	EntityManager::SetComponentData(happy4, s);

	Entity teapot1K = ConstructEntityFromBin(modelArchetype, "geometry/teapot1K.bin");
	t.Value = glm::vec3(20.0f, 5.0f, 20.0f);
	s.Value = glm::vec3(0.1f);
	EntityManager::SetComponentData(teapot1K, t);
	EntityManager::SetComponentData(teapot1K, s);
	
	Entity teapot57K = ConstructEntityFromBin(modelArchetype, "geometry/teapot57K.bin");
	t.Value = glm::vec3(0.0f, 5.0f, 20.0f);
	s.Value = glm::vec3(0.1f);
	EntityManager::SetComponentData(teapot57K, t);
	EntityManager::SetComponentData(teapot57K, s);

#endif
	
	InitGround();
	bool loopable = true;
	//Start engine. Here since we need to inject procedures to the main engine loop we need to manually loop by our self.
	while (loopable) {
		Application::PreUpdate();
		float time = Application::GetWorld()->Time()->Time();
		
#ifdef ASSIGNMENT_1
		position = CS535::RotateAround(CS535::vec3(0, 20, 0), CS535::vec3(0, 0, 10), CS535::vec3(0, 10, -10), CS535::Radians(time * 30.0f));
		pointMatrix = CS535::Translate(CS535::mat4::Identity(), position) * CS535::Scale(CS535::mat4::Identity(), CS535::vec3(1.0, 1.0, 1.0));
		ltw.Value = ConvertMat4(pointMatrix);
		EntityManager::SetComponentData(point, ltw);
#endif

#ifdef ASSIGNMENT_2
		
		ImGui::Begin("Wire-frame control");

		ImGui::End();
#endif

#pragma region Lights
#pragma region Apply lights
		LightSettingMenu();
		Rotation r;
		r.Value = glm::quatLookAt(
			glm::normalize(glm::vec3(
				glm::cos(glm::radians(lightAngle0)) * glm::sin(glm::radians(lightAngle1)),
				glm::sin(glm::radians(lightAngle0)),
				glm::cos(glm::radians(lightAngle0)) * glm::cos(glm::radians(lightAngle1))))
			, glm::vec3(0, 1, 0));
		EntityManager::SetComponentData<Rotation>(dle, r);
		dlc->specular = glm::vec3(255, 255, 255) * lightSpecular / 256.0f;
		dlc->diffuse = glm::vec3(255, 255, 251) * lightDiffuse / 256.0f;
		dlc->lightSize = lightSize;
		LightingManager::SetPCSSScaleFactor(pcssScale);
#pragma endregion
#pragma endregion

		Application::Update();
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

void EngineSetup()
{
	//LightingManager::SetAmbientLight(0.5f);
#pragma region Lighting and Shadow settings
	LightingManager::SetDirectionalLightResolution(1024);
	LightingManager::SetStableFit(true);
	LightingManager::SetSeamFixRatio(0.05f);
	LightingManager::SetMaxShadowDistance(100);
	LightingManager::SetVSMMaxVariance(0.001f);
	LightingManager::SetEVSMExponent(80.0f);
	LightingManager::SetSplitRatio(0.15f, 0.3f, 0.5f, 1.0f);
#pragma endregion
	FileIO::SetResourcePath("../UniEngine/Resources/");
	Application::Init();

#pragma region Preparations
	World* world = Application::GetWorld();
	WorldTime* time = world->Time();
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(20.0f);
	ccs->Enable();
	ccs->EnableWindowControl(false);
	ccs->SetPosition(glm::vec3(0, 20, 60));
#pragma endregion
}

Entity ConstructEntityFromBin(EntityArchetype entityArchetype, std::string path)
{
	Mesh* mesh = new Mesh();
	mesh->LoadBin(path);
	auto* mmc = new MeshMaterialComponent();
	mmc->_Mesh = mesh;
	mmc->_Material = Default::Materials::StandardMaterial;

	Entity ret = EntityManager::CreateEntity(entityArchetype);
	EntityManager::SetSharedComponent(ret, mmc);
	return ret;
}

void LightSettingMenu() {
	ImGui::Begin("Light Angle Controller");
	ImGui::SliderFloat("Angle", &lightAngle0, 0.0f, 89.0f);
	ImGui::SliderFloat("Circle", &lightAngle1, 0.0f, 360.0f);
	ImGui::SliderFloat("Diffuse", &lightDiffuse, 0.0f, 2.0f);
	ImGui::SliderFloat("Specular", &lightSpecular, 0.0f, 2.0f);
	ImGui::SliderFloat("PCSS Scale", &pcssScale, 0.0f, 3.0f);
	ImGui::SliderFloat("Light Size", &lightSize, 0.0f, 5.0f);
	ImGui::End();
}