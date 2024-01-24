#include "ui.h"
#include "xorstr.h"

#include "../config/config.h"
#include "../globals/globals.h"
#include "../input_manager/input_manager.h"
#include "../modules/modules.h"

#include "../../utils/utils.h"

ui g_ui;

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
	ImGui::Begin(X_("l4d2-internal-base"), &m_opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	{
		ImGui::Checkbox(X_("auto pistol"), &g_var.m_auto_pistol_var);
		ImGui::Checkbox(X_("triggerbot"), &g_var.m_trigger_bot_var);
		if (g_var.m_trigger_bot_var)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosX(370);
			if (ImGui::ButtonWithCustomID(ImGui::IsPopupOpen(X_("##triggerbot")) ? X_("-") : X_("+"), X_("##triggerbot_button")))
				ImGui::OpenPopup(X_("##triggerbot"));

			if (ImGui::BeginPopup(X_("##triggerbot")))
			{
				ImGui::Checkbox(X_("team"), &g_var.m_trigger_bot_team_var);
				ImGui::Separator();
				ImGui::Checkbox(X_("head"), &g_var.m_trigger_bot_head);
				ImGui::Checkbox(X_("body"), &g_var.m_trigger_bot_body);
				ImGui::Checkbox(X_("left arm"), &g_var.m_trigger_bot_left_arm);
				ImGui::Checkbox(X_("right arm"), &g_var.m_trigger_bot_right_arm);
				ImGui::Checkbox(X_("left leg"), &g_var.m_trigger_bot_left_leg);
				ImGui::Checkbox(X_("right leg"), &g_var.m_trigger_bot_right_leg);

				ImGui::EndPopup();
			}
		}

		ImGui::Checkbox(X_("knifebot"), &g_var.m_knifebot_var);
		if (g_var.m_knifebot_var)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosX(370);
			if (ImGui::ButtonWithCustomID(ImGui::IsPopupOpen(X_("##knifebot")) ? X_("-") : X_("+"), X_("##knifebot_button")))
				ImGui::OpenPopup(X_("##knifebot"));

			if (ImGui::BeginPopup(X_("##knifebot")))
			{
				ImGui::Checkbox(X_("team"), &g_var.m_knifebot_team_var);
				ImGui::SliderFloat(X_("distance"), &g_var.m_knifebot_distance_var, 40.0f, 80.0f, X_("%.0fm"));

				ImGui::EndPopup();
			}
		}

		ImGui::Checkbox(X_("drop objects"), &g_var.m_visuals_drop_var);
		if (g_var.m_visuals_drop_var)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosX(370);
			if (ImGui::ButtonWithCustomID(ImGui::IsPopupOpen(X_("##drop_objects")) ? X_("-") : X_("+"), X_("##drop_objects_button")))
				ImGui::OpenPopup(X_("##drop_objects"));

			if (ImGui::BeginPopup(X_("##drop_objects")))
			{
				ImGui::SliderFloat(X_("distance"), &g_var.m_visuals_drop_distance, 300.0f, 5000.0f, X_("%.0fm"));
				ImGui::ColorEdit4(X_("color"), g_var.m_visuals_drop_color_var);
				ImGui::Combo(X_("type"), &g_var.m_visuals_drop_type_var, X_("text\0icon"));

				ImGui::EndPopup();
			}
		}

		ImGui::Checkbox(X_("players"), &g_var.m_esp_player_name_var);
		if (g_var.m_esp_player_name_var)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosX(370);
			if (ImGui::ButtonWithCustomID(ImGui::IsPopupOpen(X_("##player_name")) ? X_("-") : X_("+"), X_("##player_name_button")))
				ImGui::OpenPopup(X_("##player_name"));

			if (ImGui::BeginPopup(X_("##player_name")))
			{
				ImGui::ColorEdit4(X_("color"), g_var.m_esp_player_name_color_var);

				ImGui::EndPopup();
			}
		}

		ImGui::Checkbox(X_("infected"), &g_var.m_esp_infected_var);
		if (g_var.m_esp_infected_var)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosX(370);
			if (ImGui::ButtonWithCustomID(ImGui::IsPopupOpen(X_("##infected")) ? X_("-") : X_("+"), X_("##infected_button")))
				ImGui::OpenPopup(X_("##infected"));

			if (ImGui::BeginPopup(X_("##infected")))
			{
				ImGui::SliderFloat(X_("distance"), &g_var.m_esp_infected_distance_var, 300.0f, 5000.0f, X_("%.0fm"));
				ImGui::ColorEdit4(X_("color"), g_var.m_esp_infected_color_var);

				ImGui::EndPopup();
			}
		}

		ImGui::Checkbox(X_("especially infected"), &g_var.m_esp_special_infected_var);
		if (g_var.m_esp_special_infected_var)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosX(370);
			if (ImGui::ButtonWithCustomID(ImGui::IsPopupOpen(X_("##especially_infected")) ? X_("-") : X_("+"), X_("##especially_infected_button")))
				ImGui::OpenPopup(X_("##especially_infected"));

			if (ImGui::BeginPopup(X_("##especially_infected")))
			{
				ImGui::ColorEdit4(X_("color"), g_var.m_esp_special_infected_color_var);

				ImGui::EndPopup();
			}
		}

		ImGui::Checkbox(X_("speedhack"), &g_var.m_speed_hack_var);
		if (g_var.m_speed_hack_var)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosX(370);
			if (ImGui::ButtonWithCustomID(ImGui::IsPopupOpen(X_("##speed_hack")) ? X_("-") : X_("+"), X_("##speed_hack_button")))
				ImGui::OpenPopup(X_("##speed_hack"));

			if (ImGui::BeginPopup(X_("##speed_hack")))
			{
				ImGui::Combo(X_("mode"), &g_var.m_speed_hack_mode_var, X_("on button (E)\0on use\0on moving\0on fire"));
				ImGui::SliderFloat(X_("speed"), &g_var.m_speed_hack_speed_var, 0.5f, 10.0f);
				ImGui::EndPopup();
			}
		}

		ImGui::Checkbox(X_("bunnyhop"), &g_var.m_bunny_hop_var);

		ImGui::Separator();

		if (ImGui::Button(X_("load")))
			g_cfg.load_cfg(X_("config.json"));

		ImGui::SameLine();

		if (ImGui::Button(X_("save")))
			g_cfg.save_cfg(X_("config.json"));

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
	g_ui.m_opened = !g_ui.m_opened;
	g_l4d2.m_surface->set_cursor_always_visible(g_ui.m_opened);
}

bool ImGui::ButtonWithCustomID(const char* label, const char* label_id)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label_id);
	const ImVec2 label_size = CalcTextSize(label, NULL, true);

	ImVec2 size_arg = ImVec2(20, 20);
	ImGuiButtonFlags flags = ImGuiButtonFlags_None;

	ImVec2 pos = window->DC.CursorPos;
	if ((ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset)
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ItemSize(size, style.FramePadding.y);
	if (!ItemAdd(bb, id))
		return false;

	if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;

	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

	const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);

	RenderNavHighlight(bb, id);
	RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
	RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

	return pressed;
}