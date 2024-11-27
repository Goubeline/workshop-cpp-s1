#include <complex>
#include <cmath>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <sil/sil.hpp>

#include "random.hpp"
#include "utils/utils.hpp"

int diverge(std::complex<float> c)
{
    std::complex<float> z = c;
    int i = 0;
    while(std::abs(z) <= 2 && i < 30)
    {
        z = z * z + c;
        i++;
    }
    return i;
}

sil::Image mandelbrot()
{
    sil::Image image{500/*width*/, 500/*height*/};
    std::complex<float> c;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            c = {(static_cast<float>(x - 333) / 166), (static_cast<float>(y - 249) / 166)};
            image.pixel(x, y) = glm::vec3{diverge(c) / 30.f};
        }
    }
    return image;
}

glm::vec3 rgb_to_hsl(glm::vec3 color)
{
    float r = color.r;
    float g = color.g;
    float b = color.b;

    float cmin = std::min(r, std::min(g, b));
    float cmax = std::max(r, std::min(g, b));
    float delta = cmax - cmin;
    float h = 0;
    float s = 0;
    float l = 0;

  // Calculate hue
  // No difference
    if (delta == 0)
        h = 0;
  // Red is max
    else if (cmax == r)
        h = (g - b) / delta + ((g < b) ? 0 : 6);
  // Green is max
    else if (cmax == g)
        h = (b - r) / delta + 2;
  // Blue is max
    else
        h = (r - g) / delta + 4;

    h /= 6;
    
    // Calculate lightness
    l = (cmax + cmin) / 2;

    // Calculate saturation
    s = (delta == 0) ? 0 : delta / (1 - std::abs(2 * l - 1));
    color.r = h;
    color.g = s;
    color.b = l;
    return color;
}

float hueToRgb(float p, float q, float t)
{
    if (t < 0) 
        t += 1;
    if (t > 1) 
        t -= 1;
    if (t < 1/6) 
        return p + (q - p) * 6 * t;
    if (t < 1/2) 
        return q;
    if (t < 2/3) 
        return p + (q - p) * (2/3 - t) * 6;
    return p;
}

glm::vec3 hsl_to_rgb(glm::vec3 color)
{
    float q = (color[2] < 0.5) ? color[2] * (1 + color[1]) : color[2] + color[1] - color[2] * color[1];
    float p = 2 * color[2] - q;
    color.g = hueToRgb(p, q, color[0]);
    color.b = hueToRgb(p, q, color[0] - 1/3);
    color.r = hueToRgb(p, q, color[0] + 1/3);
    return color;
}



sil::Image normalize_histogram(sil::Image image)
{
    std::vector<float> luminance_vec(image.pixels().size());
    float lumi_min = 1;
    float lumi_max = 0;
    for (size_t i = 0; i < image.pixels().size(); i++)
    {
        glm::vec3& color = image.pixels()[i];
        float luminance = brightness(color);
        luminance_vec[i] = luminance;
        if (luminance < lumi_min)
        {
            lumi_min = luminance;
        }
        else if (luminance > lumi_max)
        {
            lumi_max = luminance;
        }
    }

    glm::vec3 color;
    for (glm::vec3 pixel : image.pixels())
    {
        pixel = (pixel - lumi_min) * (1 / (lumi_max - lumi_min));
        // color = rgb_to_hsl(pixel);
        // color[2] = (color[2] - lumi_min) + (lumi_max - lumi_min) / 2;
        // pixel = hsl_to_rgb(color);
    }
    return image;
}

void recur_bayer_matrix(std::vector<std::vector<float>>& matrice, int n)
{
    if (n <= 0)
    {
        return;
    }

    std::vector<std::vector<float>> bigger(matrice.size() * 2);
    for (size_t i = 0; i < matrice.size(); i++)
    {
        bigger[i] = std::vector<float>(matrice.size() * 2);
        bigger[matrice.size() + i] = std::vector<float>(matrice.size() * 2);

        for (size_t j = 0; j < matrice.size(); j++)
        {
            bigger[i][j] = 4 * matrice[i][j];
            bigger[matrice.size() + i][j] = 4 * matrice[i][j] + 3;
            bigger[i][matrice.size() + j] = 4 * matrice[i][j] + 2;
            bigger[matrice.size() + i][matrice.size() + j] = 4 * matrice[i][j] + 1;
        }
    }
    matrice = bigger;
    recur_bayer_matrix(matrice, n - 1); 
}

std::vector<std::vector<float>> bayer_matrix(int n)
{
    std::vector<std::vector<float>> matrice = {{0}};
    recur_bayer_matrix(matrice, n);

    float factor = matrice.size() * matrice.size();
    for (size_t i = 0; i < matrice.size(); i++)
    {
        for (size_t j = 0; j < matrice.size(); j++)
        {
            matrice[i][j] = matrice[i][j] / factor - 0.5;
        }
    } 
    return matrice;
}

sil::Image dithering(sil::Image image)
{
    std::vector<std::vector<float>> matrice = bayer_matrix(2);
    for (int x{0}; x < image.width(); x++)
    {
        float bayer_value;
        for (int y{0}; y < image.height(); y++)
        { 
            glm::vec3& pixel = image.pixel(x, y);
            bayer_value =  matrice[x % matrice.size()][y % matrice.size()];
            pixel = glm::vec3{(pixel.r + bayer_value < 0.5) ? 0 : 1, (pixel.g + bayer_value < 0.5) ? 0 : 1, (pixel.b + bayer_value < 0.5) ? 0 : 1};
        }
    }
    return image;
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

sil::Image vortex(sil::Image image)
{
    float pi = 3.141592653589793;
    int rotax;
    int rotay;
    sil::Image copy(image.width(), image.height());
    glm::vec2 center = {(image.width() + 1) / 2, (image.height() + 1) / 2};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec2 new_pos = rotated({x, y}, center, 125 * pi * sqrt(glm::distance({x, y}, center)) / image.width());
            rotax = new_pos[0];
            rotay = new_pos[1];
            if ((0 <= rotax && rotax < image.width()) && (0 <= rotay && rotay < image.height()))
            {
                copy.pixel(x, y) = image.pixel(new_pos[0], new_pos[1]);
            }
            else
            {
                
            }
        }
    }
    return copy;
}