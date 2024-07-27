#include "ui.h"
#include "ui_tricks.h"

#include "../config/config.h"
#include "../globals/globals.h"
#include "../modules/modules.h"
#include "../input_manager/input_manager.h"

ui g_ui;

std::vector<std::string> m_configs = { "1", "2", "3", "4", "5" };

void ui::run()
{
	if (!m_opened)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, 0.0f);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.09f, 0.09f, 0.09f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.26f, 0.59f, 0.98f, 0.67f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.16f, 0.29f, 0.48f, 1.00f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.16f, 0.29f, 0.48f, 1.00f));

	ImGui::SetNextWindowSize(ImVec2(400, 350));
	ImGui::Begin(X_("Left 4 Dead 2"), &m_opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	{
		ImGui::Checkbox(X_("auto pistol"), &g_var.m_auto_pistol_var);

		ImGui::MakePopup(X_("triggerbot"), &g_var.m_trigger_bot_var, []() {
			ImGui::Checkbox(X_("team"), &g_var.m_trigger_bot_team_var);
			ImGui::Separator();
			ImGui::Checkbox(X_("head"), &g_var.m_trigger_bot_head);
			ImGui::Checkbox(X_("body"), &g_var.m_trigger_bot_body);
			ImGui::Checkbox(X_("left arm"), &g_var.m_trigger_bot_left_arm);
			ImGui::Checkbox(X_("right arm"), &g_var.m_trigger_bot_right_arm);
			ImGui::Checkbox(X_("left leg"), &g_var.m_trigger_bot_left_leg);
			ImGui::Checkbox(X_("right leg"), &g_var.m_trigger_bot_right_leg);
		});

		ImGui::MakePopup(X_("knifebot"), &g_var.m_knifebot_var, []() {
			ImGui::Checkbox(X_("team"), &g_var.m_knifebot_team_var);
			ImGui::SliderFloat(X_("distance"), &g_var.m_knifebot_distance_var, 40.0f, 80.0f, X_("%.0fm"));
		});

		ImGui::MakePopup(X_("drop objects"), &g_var.m_visuals_drop_var, []() {
			ImGui::SliderFloat(X_("distance"), &g_var.m_visuals_drop_distance, 300.0f, 5000.0f, X_("%.0fm"));
			ImGui::ColorEdit4(X_("color"), g_var.m_visuals_drop_color_var);
			ImGui::Combo(X_("type"), &g_var.m_visuals_drop_type_var, "text\0icon");
		});

		ImGui::MakePopup(X_("players"), &g_var.m_esp_player_name_var, []() {
			ImGui::ColorEdit4(X_("color"), g_var.m_esp_player_name_color_var);
		});

		ImGui::MakePopup(X_("infected"), &g_var.m_esp_infected_var, []() {
			ImGui::SliderFloat(X_("distance"), &g_var.m_esp_infected_distance_var, 300.0f, 5000.0f, X_("%.0fm"));
			ImGui::ColorEdit4(X_("color"), g_var.m_esp_infected_color_var);
		});

		ImGui::MakePopup(X_("especially infected"), &g_var.m_esp_special_infected_var, []() {
			ImGui::ColorEdit4(X_("color"), g_var.m_esp_special_infected_color_var);
		});

		ImGui::MakePopup(X_("speedhack"), &g_var.m_speed_hack_var, []() {
			ImGui::Combo(X_("mode"), &g_var.m_speed_hack_mode_var, "on button (E)\0on use\0on moving\0on fire");
			const float def_speed_val = 1.0f;
			ImGui::SliderFloat(X_("speed"), &g_var.m_speed_hack_speed_var, def_speed_val, 10.0f, X_("%.2f"));
			if (g_var.m_speed_hack_speed_var == def_speed_val)
				ImGui::Text(X_("1.00 is the default value"));
		});

		ImGui::Checkbox(X_("bunnyhop"), &g_var.m_bunny_hop_var);

		ImGui::Separator();

		ImGui::PushItemWidth(295);

		ImGui::Combo(X_("##"), &g_var.m_cfg_index, [](void* vec, int idx, const char** out_text) {
			std::vector<std::string>* vector = reinterpret_cast<std::vector<std::string>*>(vec);
			if (idx < 0 || idx >= vector->size()) return false;
			*out_text = vector->at(idx).c_str();
			return true;
		}, reinterpret_cast<void*>(&m_configs), m_configs.size());

		ImGui::SameLine();

		if (ImGui::Button(X_("load")))
			g_cfg.load_cfg(m_configs[g_var.m_cfg_index]);

		ImGui::SameLine();

		if (ImGui::Button(X_("save")))
			g_cfg.save_cfg(m_configs[g_var.m_cfg_index]);

		ImGui::Separator();

		if (ImGui::Button(X_("unload")))
			g.m_unload = true;
	}
	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void ui::initialize(IDirect3DDevice9* device)
{
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(g_input.get_window());

	ImGui::StyleColorsDark();

	ImGui::GetIO().IniFilename = {};
	ImGui::GetIO().LogFilename = {};

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	ImGui_ImplDX9_Init(device);
}

void ui::undo()
{
	if (m_opened && g_l4d2.m_surface->is_cursor_visible())
		g_l4d2.m_surface->set_cursor_always_visible(false);
}

void ui::toggle()
{
	m_opened = !m_opened;
	g_l4d2.m_surface->set_cursor_always_visible(m_opened);
}
