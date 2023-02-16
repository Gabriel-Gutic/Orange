#include "pchOrange.h"
#include "Transform.h"

#include <imgui/imgui.h>


namespace Orange
{
    Transform::Transform(const Float2& position, const Float2& scale, float rotation)
        :Position(position), Scale(scale), Rotation(rotation)
    {
    }

    Mat3 Transform::ToMat3() const
    {
        return Math::Translate(Position) * Math::Scale(Scale) * Math::Rotate(Rotation);
    }

    void Transform::ToImGui()
    {
        ImGui::DragFloat2("Position", Position.ToPtr(), 0.5f);
        ImGui::DragFloat2("Scale", Scale.ToPtr(), 0.5f);
        ImGui::DragFloat("Rotation", &Rotation);
    }
}


