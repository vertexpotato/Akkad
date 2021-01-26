#include "SceneHierarchyPanel.h"
#include "PropertyEditorPanel.h"
#include "ViewPortPanel.h"
#include "Editor/EditorLayer.h"

#include <Akkad/Application/Application.h>
#include <Akkad/ECS/SceneManager.h>
#include <Akkad/ECS/Components/TagComponent.h>
#include <imgui.h>
#include <entt/entt.hpp>
namespace Akkad {
	bool SceneHierarchyPanel::showPanel;

	SceneHierarchyPanel::SceneHierarchyPanel()
	{
	}

	void SceneHierarchyPanel::DrawImGui()
	{
		DrawHierarchyPanel();
	}

	void SceneHierarchyPanel::OnClose()
	{
		showPanel = false;
	}

	void SceneHierarchyPanel::DrawHierarchyPanel()
	{
		SharedPtr<Scene> scene;
		ViewPortPanel* viewport = (ViewPortPanel*)PanelManager::GetPanel("viewport");

		if (viewport->IsPlaying)
		{
			scene = Application::GetSceneManager()->GetActiveScene();
		}
		else
		{
			scene = EditorLayer::GetActiveScene();
		}

		ImGui::Begin("Hierarchy", &showPanel);
		
		auto view = scene->m_Registry.view<TagComponent>();

		unsigned int count = 0;
		for (auto entity : view)
		{
			auto& tag = view.get<TagComponent>(entity);

			if (ImGui::TreeNode((void*)count, tag.Tag.c_str()))
			{
				if (ImGui::IsItemToggledOpen())
				{
					if (!PropertyEditorPanel::showPanel)
					{
						PropertyEditorPanel* panel = new PropertyEditorPanel();
						PanelManager::AddPanel(panel);
						Entity e = scene->GetEntity(entity);
						PropertyEditorPanel::SetActiveEntity(e);
					}
					Entity e = scene->GetEntity(entity);
					PropertyEditorPanel::SetActiveEntity(e);
				}
				ImGui::TreePop();
			}

			if (ImGui::BeginPopupContextItem(tag.Tag.c_str()))
			{
				if (ImGui::Button("Delete"))
				{
					EditorLayer::GetActiveScene()->m_Registry.destroy(entity);
				}
				ImGui::EndPopup();
			}
			count++;

		}

		ImGui::End();
	}
}