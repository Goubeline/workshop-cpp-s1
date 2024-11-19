#include <sil/sil.hpp>

#include "random.hpp"

sil::Image luminosityup(sil::Image image)
{
    float buffer;
    for (glm::vec3& color : image.pixels())
    {
        color = sqrt(color);
    }
    return image;
}

sil::Image luminositydown(sil::Image image)
{
    float buffer;
    for (glm::vec3& color : image.pixels())
    {
        color = color*color;
    }
    return image;
}

sil::Image noise(sil::Image image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (random_int(0, 5) == 0)
            {
                image.pixel(x, y) = glm::vec3{random_float(0, 1), random_float(0, 1), random_float(0, 1)};
            }
        }
    }
    return image;
}

sil::Image mirror(sil::Image image)
{
    glm::vec3 color{};
    for (int x{0}; x < image.width()/2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            color = image.pixel(x, y);
            image.pixel(x, y) = image.pixel(image.width() - x - 1, y);
            image.pixel(image.width() - x - 1, y) = color;
        }
    }
    return image;
}

sil::Image rotate90(sil::Image image)
{
    sil::Image copie(image.height(), image.width());
    for (int x{0}; x < copie.width(); x++)
    {
        for (int y{0}; y < copie.height(); y++)
        {
            copie.pixel(x, y) = image.pixel(y, x);
        }
    }
    return mirror(copie);
}

sil::Image rgb_split(sil::Image image)
{
    sil::Image resultat(image.width(), image.height());
    for (int x{0}; x < resultat.width() - 20; x++)
    {
        for (int y{0}; y < resultat.height(); y++)
        {
            resultat.pixel(x, y).b = image.pixel(x + 20, y).b;
        }
    }
    for (int x{0}; x < resultat.width(); x++)
    {
        for (int y{0}; y < resultat.height(); y++)
        {
            resultat.pixel(x, y).g = image.pixel(x, y).g;
        }
    }
    for (int x{20}; x < resultat.width(); x++)
    {
        for (int y{0}; y < resultat.height(); y++)
        {
            resultat.pixel(x, y).r = image.pixel(x - 20, y).r;
        }
    }
    return resultat;
}