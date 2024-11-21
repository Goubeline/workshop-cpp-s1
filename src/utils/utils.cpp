
#include <sil/sil.hpp>

void colorize(sil::Image& image, glm::vec3 const& color)
{
    for (glm::vec3& pixel : image.pixels())
    {
        pixel = color;
    }
}

float brightness(glm::vec3 const& color)
{
    return (0.2126f*color.r + 0.7152f*color.g + 0.0722f*color.b);
}

void srgb_to_linear(glm::vec3& color)
{
    for (int i = 0; i < 3; i++)
    {
        if (color[i] <= 0.0404482362771082)
            color[i] /= 12.92;
        else
            color[i] = pow(((color[i] + 0.055) / 1.055), 2.4);
    }
}

void linear_to_srgb(glm::vec3& color)
{
    for (int i = 0; i < 3; i++)
    {
        if (color[i] > 0.0031308)
            color[i] = 1.055 * (pow(color[i], (1.0 / 2.4))) - 0.055;
        else
            color[i] *= 12.92;
    }
}