#pragma once

#include<string>

#include "../../inc/types.h"

namespace radar_util {
    Blip add_blip_at_coords(Hash blip_hash, float scale, const std::string& blip_name, const Vector3& blip_coords);
    void remove_blip(Blip blip);
}
