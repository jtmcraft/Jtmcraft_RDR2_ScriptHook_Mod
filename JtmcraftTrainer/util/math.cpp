#include "math.h"

#include <cmath>

#include "../../../inc/natives.h"

constexpr float pi = 3.14159265358979323846f;

float math::degrees_to_radians(const float degrees) {
    return degrees  * pi / 180.0f;
}

Vector3 math::rotation_to_direction_unit_vector(const Vector3& rotation) {
    const float radian_x = degrees_to_radians(rotation.x);
    const float radian_z = degrees_to_radians(rotation.z);
    const float rotation_scaling = abs(cos(radian_x));
 
    const float x_component = -sin(radian_z) * rotation_scaling;
    const float y_component = cos(radian_z) * rotation_scaling;
    const float z_component = sin(radian_x);

    return Vector3 {
        x_component,
        y_component,
        z_component
    };
}

Vector3 math::forward_vector(const Entity& entity, const Vector3& scaling_vector, const bool is_safe_for_ped) {
    const Vector3 entity_coords = ENTITY::GET_ENTITY_COORDS(entity, true, true);
    const Vector3 forward_vector = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
    Vector3 result_vector {
        entity_coords.x + forward_vector.x * scaling_vector.x,
        entity_coords.y + forward_vector.y * scaling_vector.y,
        entity_coords.z + forward_vector.z * scaling_vector.z
    };

    if (is_safe_for_ped) {
        PATHFIND::GET_SAFE_COORD_FOR_PED(result_vector.x, result_vector.y, result_vector.z, true, &result_vector, 16);
    }

    return result_vector;
}
