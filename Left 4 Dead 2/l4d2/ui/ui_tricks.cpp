#include "ui_tricks.h"

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

void ImGui::MakePopup(const char* name, bool* v, std::function<void(void)> func)
{
	std::string pop_name = name;

	Checkbox(name, v);

	if (*v) {
		SameLine();
		SetCursorPosX(370);
		if (ButtonWithCustomID(IsPopupOpen(pop_name.c_str()) ? X_("-") : X_("+"), std::string(pop_name + X_("popup")).c_str()))
			OpenPopup(pop_name.c_str());

		if (BeginPopup(pop_name.c_str())) {
			func();
			EndPopup();
		}
	}
}