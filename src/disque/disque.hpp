#pragma once

#include <sil/sil.hpp>

struct Make_circle{
    int ray = 100;
    std::pair<int, int> center = std::make_pair(249, 249);
    int thickness = ray/9;
    glm::vec3 const& background_color = glm::vec3{0};
    glm::vec3 const& front_color = glm::vec3{1};
};

sil::Image disk(Make_circle data);
sil::Image circle(Make_circle data);
void anim(Make_circle data, int nb_frames);
sil::Image rosace(Make_circle data);