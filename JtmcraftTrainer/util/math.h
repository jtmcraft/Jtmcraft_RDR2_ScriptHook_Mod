#pragma once
#include "../../inc/types.h"

namespace math_util {
    float degrees_to_radians(float degrees);
    Vector3 rotation_to_direction_unit_vector(const Vector3& rotation);
    Vector3 forward_vector(const Entity& entity, const Vector3& scaling_vector, bool is_safe_for_ped);
}
