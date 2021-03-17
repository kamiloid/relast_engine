#include"Transform_control.h"

namespace addons
{
	namespace transform
	{
		const char* _trans_item[] = { "Global", "Local" };
		const char* _transform_items[] = { _GLOBAL_, _LOCAL_ };
		Relast::enums::TRANSFORM_TYPE _transform_types[] =
		{
			Relast::enums::TRANSFORM_TYPE::TT_GLOBAL,
			Relast::enums::TRANSFORM_TYPE::TT_LOCAL
		};
		Relast::enums::TRANSFORM_TYPE _selected_transform_type = Relast::enums::TRANSFORM_TYPE::TT_GLOBAL;
		INT _transform_type = 0;
		Relast::enums::TRANSFORM_OPERATION _control = Relast::enums::TRANSFORM_OPERATION::TO_TRANSLATE;
	}
}

void addons::transform::init(Relast::Rectf viewport_size)
{
	bool open;
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 win_size = ImGui::GetWindowSize();
	//ImGui::SetNextWindowPos(ImVec2(viewport_size._w / 2 - win_size.y / 2, 30));
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2 - win_size.y / 2, 30));
	ImGui::Begin("Transform", &open, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

	if (ImGui::Button("Translate"))
		_control = Relast::enums::TRANSFORM_OPERATION::TO_TRANSLATE;
	ImGui::SameLine();
	if (ImGui::Button("Rotate"))
		_control = Relast::enums::TRANSFORM_OPERATION::TO_ROTATE;
	ImGui::SameLine();
	if (ImGui::Button("Scale"))
		_control = Relast::enums::TRANSFORM_OPERATION::TO_SCALE;
	ImGui::SameLine();

	INT trans_items_l = sizeof(_trans_item) / sizeof(*_trans_item);
	const char* transfor_type = _trans_item[_transform_type];
	if (ImGui::BeginCombo("Transform", transfor_type, ImGuiComboFlags_NoArrowButton))
	{
		for (INT i = 0; i < trans_items_l; i++)
		{
			bool is_selected = (_transform_type == i);
			if (ImGui::Selectable(_trans_item[i], is_selected))
			{
				_transform_type = i;
				_selected_transform_type = _transform_types[i];
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::End();
}

Relast::enums::TRANSFORM_TYPE addons::transform::get_transform_type()
{
	return _selected_transform_type;
}

Relast::enums::TRANSFORM_OPERATION addons::transform::get_transform_operation()
{
	return _control;
}