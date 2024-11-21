#pragma once

#include <sil/sil.hpp>

sil::Image glitch(sil::Image image);
sil::Image sort_pixels(sil::Image image);
sil::Image degrade_color(glm::vec3 start_color, glm::vec3 end_color);