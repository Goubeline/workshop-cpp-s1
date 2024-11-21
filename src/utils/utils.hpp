#include <sil/sil.hpp>

void colorize(sil::Image& image, glm::vec3 const& color);
float brightness(glm::vec3 const& color);
void srgb_to_linear(glm::vec3& color);
void linear_to_srgb(glm::vec3& color);