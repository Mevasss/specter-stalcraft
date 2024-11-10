#include "Menu.h"
#include "../../Libs/Imgui/imgui_impl_win32.h"
#include "../../Libs/Imgui/imgui_impl_opengl2.h"
auto Menu::draw() -> void
{
	ImGui::Begin("Specter - Stalcraft", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Checkbox("Items esp",&items_esp);
	ImGui::ColorEdit4("Items esp color", (float*)&items_esp_color);
	ImGui::Checkbox("Players chams", &players_chams);
	ImGui::ColorEdit4("Players chams color", (float*)&players_chams_color);
	ImGui::Hotkey(&players_toggle_key, { 100,25 });
	ImGui::Text("Players toggle key");


	ImGui::End();
}
