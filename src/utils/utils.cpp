
#include <sil/sil.hpp>

void colorize(sil::Image& image, glm::vec3 const& color)
{
    for (glm::vec3& pixel : image.pixels())
    {
        pixel = color;
    }
}