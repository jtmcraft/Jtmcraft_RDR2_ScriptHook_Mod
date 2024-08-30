#include "radar.h"

#include "util.h"
#include "../../inc/natives.h"

Blip radar_util::add_blip_at_coords(Hash blip_hash, const float scale, const std::string& blip_name, const Vector3& blip_coords) {
    const Any created_blip = RADAR::_0x554D9D53F696D002(1664425300, 0, 0, 0);
    const Blip blip = static_cast<Blip>(created_blip);

    RADAR::SET_BLIP_SPRITE(blip, static_cast<int>(blip_hash), false);
    RADAR::SET_BLIP_SCALE(blip, scale);
    RADAR::_0x9CB1A1623062F402(blip, reinterpret_cast<Any*>(util::create_string(blip_name)));
    RADAR::SET_BLIP_COORDS(blip, blip_coords.x, blip_coords.y, blip_coords.z);

    return blip;
}

void radar_util::remove_blip(Blip blip) {
    if (RADAR::DOES_BLIP_EXIST(blip)) {
        RADAR::REMOVE_BLIP(&blip);
    }
}
