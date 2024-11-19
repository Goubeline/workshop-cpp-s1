#include <sil/sil.hpp>

sil::Image green_only(sil::Image image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
    return image;
}

sil::Image negativ(sil::Image image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = 1.f - color;
    }
    return image;
}

sil::Image canal_swap(sil::Image image)
{
    float buffer;
    for (glm::vec3& color : image.pixels())
    {
        buffer = color.r;
        color.r = color.g;
        color.g = buffer;
    }
    return image;
}

sil::Image black_white(sil::Image image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = glm::vec3{(0.2126f*color.r + 0.7152f*color.g + 0.0722f*color.b)};
    }
    return image;
}

sil::Image degrade()
{
    sil::Image image{300/*width*/, 200/*height*/};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) += glm::vec3{x/static_cast<float>(image.width())};
        }
    }
    return image;
}