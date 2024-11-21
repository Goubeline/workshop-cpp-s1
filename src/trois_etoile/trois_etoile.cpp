#include<algorithm>
#include <sil/sil.hpp>

#include "utils/utils.hpp"
#include "random.hpp"

void invert(sil::Image& image, std::pair<int, int> pos1, std::pair<int, int> pos2, std::pair<int, int> size)
{
    glm::vec3 buffer{};
    for (int i = 0; i < size.first; i++)
    {
        for (int j = 0; j < size.second; j++)
        {
            buffer = image.pixel(i + pos1.first, j + pos1.second);
            image.pixel(i + pos1.first, j + pos1.second) = image.pixel(i + pos2.first, j + pos2.second);
            image.pixel(i + pos2.first, j + pos2.second) = buffer;
        }
    }
}

sil::Image glitch(sil::Image image)
{
    int nb_pixels = image.height() * image.width();
    int gx;
    int gy;
    int randx;
    int randy;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (random_int(0, nb_pixels ) < 75)
            {
                gx = random_int(image.width()/20, image.width()/8);
                gy = random_int(image.height()/100, image.height()/30);
                if (gx + x >= image.width())
                {
                    gx = image.width() - x - 1;
                }
                if (gy + y >= image.height())
                {
                    gy = image.height() - y - 1;
                }
                do
                {
                    randx = random_int(0, image.width() - gx - 1);
                    randy = random_int(0, image.height() - gy - 1);
                } while ((randx <= x + gx && randx >= x - gx) && (randy <= y + gy && randy >= y - gy));

                invert(image, std::make_pair(x, y), std::make_pair(randx, randy), std::make_pair(gx, gy));
            }
        }
    }
    return image;
}

void brightness_sort(sil::Image& image, int start, int end)
{
    std::sort(image.pixels().begin() + start, image.pixels().begin() + end,
            [](glm::vec3 const& color1, glm::vec3 const& color2)
            {
                return brightness(color1) < brightness(color2); // Trie selon la luminosité des couleurs (NB : c'est à vous de coder la fonction `brightness`)
            });
}

sil::Image sort_pixels(sil::Image image)
{
    int nbpixels = image.height() * image.width();
    for(int i = 0; i < nbpixels - 70; i++)
    {
        if (!random_int(0, 140))
        {
            brightness_sort(image, i, i + 70);
            i += 70;
        }
    }
    return image;
}

void linear_srgb_to_oklab(glm::vec3& color) 
{
    float l = 0.4122214708f * color.r + 0.5363325363f * color.g + 0.0514459929f * color.b;
	float m = 0.2119034982f * color.r + 0.6806995451f * color.g + 0.1073969566f * color.b;
	float s = 0.0883024619f * color.r + 0.2817188376f * color.g + 0.6299787005f * color.b;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);


        color.r = 0.2104542553f*l_ + 0.7936177850f*m_ - 0.0040720468f*s_;
        color.g = 1.9779984951f*l_ - 2.4285922050f*m_ + 0.4505937099f*s_;
        color.b = 0.0259040371f*l_ + 0.7827717662f*m_ - 0.8086757660f*s_;
}

void oklab_to_linear_srgb(glm::vec3& color) 
{
    float l_ = color.r + 0.3963377774f * color.g + 0.2158037573f * color.b;
    float m_ = color.r - 0.1055613458f * color.g - 0.0638541728f * color.b;
    float s_ = color.r - 0.0894841775f * color.g - 1.2914855480f * color.b;

    float l = l_*l_*l_;
    float m = m_*m_*m_;
    float s = s_*s_*s_;
    
    color = {
		+4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
		-1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
		-0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}

sil::Image degrade_color(glm::vec3 start_color, glm::vec3 end_color)
{
    srgb_to_linear(start_color);
    srgb_to_linear(end_color);
    linear_srgb_to_oklab(start_color);
    linear_srgb_to_oklab(end_color); 

    sil::Image image{300/*width*/, 200/*height*/};
    glm::vec3 color;
    for (int x{0}; x < image.width(); x++)
    {
        color = glm::mix(start_color, end_color, x/static_cast<float>(image.width()));
        oklab_to_linear_srgb(color);
        linear_to_srgb(color);
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = color;
        }
    }
    return image;
}