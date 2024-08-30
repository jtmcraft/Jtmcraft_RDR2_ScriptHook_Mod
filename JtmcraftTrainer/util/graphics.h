#pragma once

#include <string>
#include <vector>

#include "../../inc/types.h"

struct ui_rectangle
{
    float top;
    float left;
    float width;
    float height;

    ui_rectangle(const float t, const float l, const float w, const float h) : top(t), left(l), width(w), height(h) {}
};

struct ui_color
{
    byte red;
    byte green;
    byte blue;
    byte alpha;

    ui_color(const byte r, const byte g, const byte b, const byte a) : red(r), green(g), blue(b), alpha(a) {}

    static const ui_color black_opaque;
    static const ui_color white_opaque;
    static const ui_color red_opaque;
};

enum class font : int
{
    body,						// Hapna Slab Serif DemiBold
    body1,						// Droid Serif Pro
    catalog1,					// RDR Gothica
    catalog2,					// RDR Catalogue Numbers
    catalog3,					// Arial DEBUG
    catalog4,					// RDR Catalogue Bold
    catalog5,					// Cabrito Norm Demi
    chalk,						// RDR Chalk Hand
    debug_bold,					// HelveticaNeue LT 47 LightCn
    fixed_width_numbers,			// RDR Lino Numbers
    font5,						// Redemption
    gamername,					// Rockstar Gamertag Cond
    handwritten,				// 1871 Dreamer Script
    ledger,						// RDR Ledger Hand
    rockstar_tag,				// RockstarTAG
    social_club_cond_bold,		// Arial
    title,						// RDR Lino
    wanted_posters_generic,		// RDR Turri
};

enum class alignment : int
{
    left,
    center,
    right
};

const std::vector<const char*> font_list = {
    "body", "body1", "catalog1", "catalog2", "catalog3", "catalog4", "catalog5", "chalk",
    "Debug_BOLD", "FixedWidthNumbers", "Font5", "gamername", "handwritten", "ledger", "RockstarTAG",
    "SOCIAL_CLUB_COND_BOLD", "title", "wantedPostersGeneric"
};

namespace graphics_util {
    float calculate_aligned_x(float screen_x, alignment text_align);
    void draw_text(const std::string& text, float x, float y);;
    void draw_center_text(const std::string& text);
    void draw_center_text(const std::string& text, int font_size, float screen_x, float screen_y, const ui_color& color, font font);
    void wait_and_draw_center_text(int millis, const std::string& text, const ui_color& color);
    void draw_rectangle(float line_left, float line_top, float width, float height, int red, int green, int blue, int alpha);
    void draw_rectangle(const ui_rectangle& rectangle, const ui_color& color);
    void draw_light(const Vector3& coords, const ui_color& color, float range, float intensity);
    void draw_light(const Vector3& coords, float range, float intensity);
    void set_entity_light_color(Entity entity, int red, int green, int blue);
    void set_entity_light_intensity(Entity entity, float intensity);
}
